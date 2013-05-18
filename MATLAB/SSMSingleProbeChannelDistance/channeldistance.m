% This is a script to run the follwoing tests
% Probe channel using probe 1 and also measure
% the distance from the tank wall

%%
% PRBS for output signal
% Set simulink parameters
%   sampling: 1e-4
%   tx: 1e3 Hz
%   Vpp: 2V
%   runtime: 0.01 sec
%   numer of samps taken: ~100

ValUinit = 0;  %: Initial steady state
Tappli = 0;    %: Application instant 
ValAmpli = 1;  %: Magnitude
ValDecal = 0;  %: Add-on DC component
ValLgReg = 10;  %: Register length (# of cells)
ValDivi = 1;   %: Frequency divider (pulse length multiplier)
Nsamp = 100;     %: Number of samples

prbs = create_prbs(ValUinit, ValAmpli, ValDecal, ValLgReg, ValDivi, Nsamp, Tappli)';
Ts = 1e-4;
t = (0:Ts:Ts*Nsamp-Ts)';
prbs_test = [t, prbs(1:Nsamp)];
stem(prbs);
%%
% Create PRBS for moving the gantry.
% Each binary sequences corresponds to either a
% movement forward or backward.
% the step size is determiend by the "stepsize" variable
% that is specifically used with the python script

stepsize = 0.5; %
ValUinit = 0;   %: Initial steady state
Tappli = 0;     %: Application instant 
ValAmpli = 1;   %: Magnitude
ValDecal = 0;   %: Add-on DC component
ValLgReg = 10;  %: Register length (# of cells)
ValDivi = 2;    %: Frequency divider (pulse length multiplier)
Nsamp = 100;    %: Number of samples
prbs_d = create_prbs(ValUinit, ValAmpli, ValDecal, ...
                   ValLgReg, ValDivi, Nsamp, Tappli)';
               
prbs_movement = prbs_d.*stepsize;
for i=2:Nsamp
    prbs_movement(i) = prbs_movement(i-1) + prbs_movement(i);
end
prbs_movement = -prbs_movement;
% Inspect the movement elements to make sure they arn't
% too large as to cause the probe to colide with the tank
stem(prbs_movement)

%% Run system test program (also need to run the python program in conjuction)
clc;

start_x = 10;
start_y = 14;
speed = 30;

fpathout = 'C:\Users\newton\AeroFS\NESL_Software\electrosense\PYTHON\scripts\matlabCOMin.txt';
fpathin = 'C:\Users\newton\AeroFS\NESL_Software\electrosense\PYTHON\scripts\matlabCOMout.txt';

% set starting position
trajectory = zeros(length(prbs_movement),3);
fidout = fopen(fpathout, 'w');
for i=1:length(prbs_movement)
    % send commands to the gantry client
    fprintf(fidout, '%.2f %.2f %.2f\n', start_x, start_y+prbs_movement(i), speed);
    trajectory(i,:) = [start_x, start_y+prbs_movement(i), speed];
end   
fclose(fidout);

status = 0;
numberOfSamples = 101;
numberOfPoints = length(prbs_movement);
OutputLog = zeros(numberOfPoints, numberOfSamples);
for i=1:length(trajectory)
    % wait until gantry is done moving
    while (status ~= trajectory(i,2))
        fidin = fopen(fpathin, 'r');
        status = fgetl(fidin);
        fclose(fidin);
        status = str2double(status);
        pause(0.001);
    end
    
    % sample using xpcTarget
    % tg.start;
    display(['location reached ',num2str(status)]);
    tg.start; pause(0.001);
    OutputLog(i,:) = tg.OutputLog(:,1)'; 
end
distanceFromWall = 22-(prbs_movement+start_y)+1.25;
% add distance from wall measurement.
OutputLog = [distanceFromWall,OutputLog];

%% Calculate the variable D in the model 
load system_model;
% x = A*x + B*u + D*d
% x: state
% u: input
% d: distance
% solve x = inv(I-A)Bu

% construct B vector with inputs from PRBS
B = sys_train.B;
B_bar = B*prbs';
B_bar = reshape(B_bar,length(B)*length(prbs),1);
B_bar_length = length(B_bar);
for i=1:7
   B_bar = [B_bar;B_bar];
end
B_bar = B_bar(1:length(prbs_movement)*B_bar_length);
% add the additional zeros
B_bar = [B_bar; 0; 0; 0];

A_bar = [sys_train.A; zeros(297,3)];
A_bar = circshift(A_bar,3);
for i=1:7
    A_bar = [A_bar,circshift(A_bar,size(A_bar,2))];
end
% truncate excess
A_bar = A_bar(1:300,1:300);
A_bar = [A_bar;zeros(size(A_bar,1)*(length(prbs)-1),size(A_bar,2))];
for i=1:7
    A_bar = [A_bar,circshift(A_bar,size(A_bar,2))];
end
%%
load OutputLog;
d = OutputLog(:,1);
identy = [1;0;0];
identy = kron(ones(100,1),identy);
dist_vector1 = kron(d,identy);
identy = [0;1;0];
identy = kron(ones(100,1),identy);
dist_vector2 = kron(d,identy);
identy = [0;0;1];
identy = kron(ones(100,1),identy);
dist_vector3 = kron(d,identy);
dist_vector = [dist_vector1,dist_vector2,dist_vector3];
% add identy at the end for the D variables
dist_vector = [dist_vector;eye(3)];
%%
A_bar_trunc = A_bar(1:30000,1:30000);
A_bar_trunc = [A_bar_trunc;zeros(3,30000)];
A_bar_trunc = [A_bar_trunc,dist_vector];
%% FAIL! Does not finish
tic;
x = (eye(30003)-A_bar_trunc)\B_bar;
toc;
%% run small truncated version of code
% parameters to determine how many sample sets to include
tic;
data_sets = 40;
sample_set = 100;
distance_set = 100;
order = size(sys_train.A,1);

B_bar_sub = B_bar(1:data_sets*order*sample_set);
B_bar_sub = [B_bar_sub;zeros(3,1)];

A_bar_sub = A_bar_trunc(1:data_sets*order*sample_set, 1:data_sets*order*sample_set);
dist_vector_sub = A_bar_trunc(1:data_sets*order*sample_set, order*sample_set*distance_set+1:end);
dist_vector_sub = [dist_vector_sub;eye(3)];
A_bar_sub = [A_bar_sub; zeros(3,data_sets*order*sample_set)];
A_bar_sub = [A_bar_sub, dist_vector_sub];

x = pinv(eye(data_sets*order*sample_set+3) - A_bar_sub)*B_bar_sub;
display(x(301:303));
toc;