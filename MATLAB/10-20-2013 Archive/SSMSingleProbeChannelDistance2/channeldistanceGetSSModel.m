% This is a script to run the follwoing tests
% Probe channel using probe 1 and also measure
% the distance from the tank wall

% 5/18/2013
% Here I tired to find the state space model with the inclusion of distance
% input data. We want to model the input signal and distance independently.
% Here we test to see whether n4sid will automatically model it
% independently for us. But this is not the case because comparing the A
% and B matrix with and without distance input are completely different.
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
Nsamp = 10;    %: Number of samples
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
for i=1:100
   rx_data = OutputLog(i,2:end);
   rx_avg = mean(rx_data);
   OutputLog(i,2:end) = OutputLog(i,2:end)-rx_avg;
end
dist = OutputLog(:,1);
dist = kron(dist,ones(100,1));
rx_data = OutputLog(:,2:101)';
rx_data = reshape(rx_data,100*100,1);
tx = kron(ones(100,1),prbs);
Ts = 1e-4;
data = iddata(rx_data,[tx,dist],Ts);
[sys_train2,x0_train2] = n4sid(data,'best'); % 'best' extimates the order
%% Implement Kalman filter
load ssdata
load OutputLog
data = OutputLog(1,2:101)';
distance = OutputLog(1,1);
saveX = zeros(size(data,1),4);
saveY = zeros(size(data,1),1);
A2 = [A, F; zeros(1,3), 1];
B2 = [B; 0];
C2 = [C'; 0];
for i=1:size(data,1);
    [y,x,K] = kalmanfilter(data(i),prbs(i),A2,B2,C2,0,0); % what is error covariance?
    
    saveX(i,:) = x';
    saveY(i) = y;
end
distancep = x(4);