% This is a script to run the following tests:
% Use probe 1,2, & 8 to move the sensor from right to left side of the tank while
% taking voltage measurements.

%5/28/2013
% Convert data structure to cells to accomodate multiple probes. Each cell
% contains the data from the probes that are active. The cells themselves
% represent data measured at different distances.
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
ValAmpli = 10;  %: Magnitude
ValDecal = 0;  %: Add-on DC component
ValLgReg = 10;  %: Register length (# of cells)
ValDivi = 1;   %: Frequency divider (pulse length multiplier)
Nsamp = 100;     %: Number of samples

prbs = create_prbs(ValUinit, ValAmpli, ValDecal, ValLgReg, ValDivi, Nsamp, Tappli)';
Ts = 1e-3;
t = (0:Ts:Ts*Nsamp-Ts)';
prbs_train = [t, prbs(1:Nsamp)];
stem(prbs);
%%
movement = 0:0.5:19;

%% Run system test program (also need to run the python program in conjuction)
% run with MovingGantry2.py
clc;

start_x = 10;
start_y = 0;
speed = 30;
pause_sec = 0.5;

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
numberOfSamples = 1000;
numberOfPoints = length(movement);
OutputLog = {};

% Write the received data of the first trajectory because once the gantry
% starts moving it will miss it and the system will then be out of sync
% becuase it waits for the gantry to move to the coordinates sequentially.
tg.start; pause(pause_sec);
OutputLog{2} = tg.OutputLog(1:numberOfSamples,1:3); 
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
    tg.start; pause(pause_sec);
    OutputLog{i+1} = tg.OutputLog(1:numberOfSamples,1:3); 
end

% calculate the set of distances
distanceFromWall = (19-(movement+start_y))';
% add distance from wall measurement.
OutputLog{1} = distanceFromWall;
trans_signal = tg.OutputLog(1:1000,4);
%% compare error between model and rx signal (no distnace incorporated)
Ts_out = 1e-4;
[A,B,C,D] = ssdata(sys_train);
sys = ss(A,B,C,D,Ts_out);
t = (0:Ts_out:Ts_out*1000-Ts_out)';
trans_signal = tg.OutputLog(1:1000,4);
[y,t,x] = lsim(sys,trans_signal,t);

% parse data
dist = OutputLog{1};
data = OutputLog(:,2:end);
data_length = size(OutputLog,2) - 1;

%%
DC = 0;
for i=2:(data_length+1);
   DC(i-1) = mean(OutputLog{i}(:,1));
end
scatter(DC',dist);
title('Sensor 1 facing directly at Left Wall')
xlabel('DC Value');
ylabel('Distance from Left Wall (inches)');
%%
% calculate errors
error_norm = zeros(data_length,1);
error_norm_DC = 0;
for i=1:data_length
    temp = data{i} - kron(ones(numberOfSamples,1),mean(data{i},1)); % DC subtraction
    error_norm(i) = norm(temp-y);
end

% subplot(2,1,1);
scatter(dist,error_norm);
xlabel('distance from wall (inches)');
ylabel('error norm between rx and model');
legend('20 Vpp');
grid on;

% subplot(2,1,2);
% scatter(dist,error_norm-mean(15:35));
% xlabel('distance from wall (inches)');
% ylabel('error norm between rx and model');
% legend('20 Vpp');
% grid on;