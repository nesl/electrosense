% This is a script to run the following tests:
% Use probe 1 to move the sensor from right to left side of the tank while
% taking voltage measurements.

% 5/20/2013
% Write script to move the gantry from right side of the tank to the left
% side of the tank. Each 0.5" traversal, we'll take 100 samples at 10 kHZ
% while transmitting a signal at 1 kHz.
% PRBS parameters
% ValUinit = 0;  %: Initial steady state
% Tappli = 0;    %: Application instant 
% ValAmpli = 1;  %: Magnitude
% ValDecal = 0;  %: Add-on DC component
% ValLgReg = 10; %: Register length (# of cells)
% ValDivi = 1;   %: Frequency divider (pulse length multiplier)
% Nsamp = 100;   %: Number of samples
%
% The effects of using 2Vpp doesn't seem to have a big effect on the
% measurement error (between tx and the rx signal), which seems random with distance right now. So rerun
% the experiment with 4Vpp and 6Vpp.
%
% Now running the experiment with 2Vpp, 4Vpp, 6Vpp and comparing the error
% between the rx signal form the sensor and the model. The results don't
% seem to change very much.
%
% Redid the system identification to get a lower error rate and now redoing
% the distance tests.
%%
% PRBS for output signal
% Set simulink parameters
%   sampling: 1e-4
%   tx: 1e3 Hz
%   Vpp: 2V
%   runtime: 0.01 sec
%   numer of samps taken: ~100

% set simulink time to 0.01
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
movement = 0:0.5:23.5;

%% Run system test program (also need to run the python program in conjuction)
% run with MovingGantry2.py or MovingGantry3.py
clc;

start_x = 10;
start_y = 0;
speed = 30;
pause_sec = 1;

fpathout = 'C:\Users\newton\AeroFS\NESL_Software\electrosense\PYTHON\scripts\matlabCOMin.txt';
fpathin = 'C:\Users\newton\AeroFS\NESL_Software\electrosense\PYTHON\scripts\matlabCOMout.txt';

% set starting position
trajectory = zeros(length(movement),3);
fidout = fopen(fpathout, 'w');
for i=1:length(movement)
    % send commands to the gantry client
    fprintf(fidout, '%.2f %.2f %.2f\n', start_x, start_y+movement(i), speed);
    trajectory(i,:) = [start_x, start_y+movement(i), speed];
end   
fclose(fidout);

status = 0;
numberOfSamples = 100;
numberOfPoints = length(movement);
OutputLog = zeros(numberOfPoints*5, numberOfSamples);

% Write the received data of the first trajectory because once the gantry
% starts moving it will miss it and the system will then be out of sync
% becuase it waits for the gantry to move to the coordinates sequentially.
for j=1:5
    tg.start; pause(pause_sec);
    OutputLog(j,:) = tg.OutputLog(1:100,1)'; 
end
% start collecting data for the rest of the distances
for i=2:length(trajectory)
    % wait until gantry is done moving
    while (status ~= trajectory(i,2))
        fidin = fopen(fpathin, 'r');
        status = fgetl(fidin);
        fclose(fidin);
        status = str2double(status);
        pause(0.01);
    end
    
    % feedback on console
    display(['location reached ',num2str(status)]);
    
    % take measurement using xpcTarget
    for j=1:5
        tg.start; pause(pause_sec);
        OutputLog((i-1)*5+j,:) = tg.OutputLog(1:100,1)'; 
    end
end

% calculate the set of distances
distanceFromWall = (23.5-(movement+start_y)+ 0.75)';
% add distance from wall measurement.

%% compare error between model and rx signal (no distnace incorporated)
[A,B,C,D] = ssdata(sys_train);
sys = ss(A,B,C,D,Ts);
[y,t,x] = lsim(sys,prbs_test(:,2),prbs_test(:,1));

dist = OutputLog(:,1);
data = OutputLog(:,2:end);
data_length = size(OutputLog,1);
for i=1:size(data,1);
    temp = data(i,:) - mean(data(i,:));
    error_norm(i) = norm(temp-y');
end
scatter(dist,error_norm');
xlabel('distance from wall (inches)');
ylabel('error norm between rx and model');
title('Tx 1Vpp');

%% compare error between model and rx signal (distance incorporated)
load ssdata;
Ts = 1e-4;
sys = ss(A,[B,F],C,D,Ts);
numofcoords = length(distanceFromWall);
ydist = zeros(numofcoords,1);
dist = OutputLog(:,1);
data = OutputLog(:,2:end);
for i=1:numofcoords
    [y,t,x] = lsim(sys, ...
                  [prbs_test(:,2),ones(length(prbs_test(:,2)),1)*distanceFromWall(i)], ...
                   prbs_test(:,1));
    temp = data(i,:) - mean(data(i,:));
    error_norm(i) = norm(data(i,:)-y');
end

scatter(dist,error_norm');
xlabel('distance from wall (inches)');
ylabel('error norm between rx and model');
title('Tx 1Vpp');