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