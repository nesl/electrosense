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
prbs = create_prbs(ValUinit, ValAmpli, ValDecal, ...
                   ValLgReg, ValDivi, Nsamp, Tappli)';
               
prbs_movement = prbs.*stepsize;
for i=2:Nsamp
    prbs_movement(i) = prbs_movement(i-1) + prbs_movement(i);
end
prbs_movement = -prbs_movement;
% Inspect the movement elements to make sure they arn't
% too large as to cause the probe to colide with the tank
stem(prbs_movement)

%%
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

%% Calculate the model 

% x_k+1 = A*x_k + B1*u_k + B2*d
% y_k = C*x_k

