% xPC Script

xpcexplr


%%

open C:\Users\newton\Dropbox\xpCTarget\ChannelProbe\UnWaterChannelProbe.mdl

%%

save('workspace');

%%

%                 ____  Valdecal + ValAmpli         __________      ____
%                |    |                            |          |    |
% Valdecal       -|----|--------                    |          |    |
%                |    |____________________________|          |____|
%                |
%                |
% ini ____________|
%                                                  |--------->|
%    |-Tappli -->|                        ValReg * ValDivi 
% 
% 
%    |---------- Nsamp ------------------------------------------------->|

ValUinit = 0;  %: Initial steady state
Tappli = 0;    %: Application instant 

ValAmpli = 0.25;  %: Magnitude
ValDecal = 0;  %: Add-on DC component

ValLgReg = 10;  %: Register length (# of cells)
ValDivi = 1;   %: Frequency divider (pulse length multiplier)

Nsamp = 2000;     %: Number of samples

prbs = create_prbs(ValUinit, ValAmpli, ValDecal, ValLgReg, ValDivi, Nsamp, Tappli)';
Ts = 1e-4;
t = (0:Ts:Ts*1000-Ts)';
prbs_train = [t, prbs(1:1000)];
prbs_test = [t, prbs(1001:2000)];

%%
% examine the step information to make sure the PRBS is valid
%tg.start
output = tg.OutputLog;
shift = 3;
NLength = size(output(shift:end,1));
TxFreq = 1e3;
Fs = 1e4;
sets = floor(NLength/(Fs/TxFreq));
sets = sets(1);
output = output(shift+1:(sets*Fs/TxFreq+shift),1);
output = reshape(output,Fs/TxFreq,sets);
average_output = mean(output,2);
average_output = average_output(1:end-1);
average_DC_output = mean(average_output);
plot(average_output);
S = stepinfo(average_output)

%% Build Model

% ONLY uncomment if you want to run the simulink model
tg.start; pause(0.1);

subplot(2,1,1)
% Tx Signal
%output = tg.OutputLog;
%stem(output(1:100,2)); axis tight;
%subplot(2,1,2)
% Rx Signal
%plot(output(1:100,1)); axis tight;

rx_train = output(:,1);
rx_average_train = mean(rx_train);
rx_train = rx_train - rx_average_train;
rx_train = rx_train(1:1000);
Ts = 1e-4;
data = iddata(rx_train, prbs_train(:,2), Ts); 
% get state-space model using subspace method
[sys_train,x0_train] = n4sid(data,'best'); % 'best' extimates the order
%% Test model
% rebuild simulink model
close all;

% ONLY uncomment if you want to run the simulink model
tg.start; pause(0.1);


% Tx Signal
output_test = tg.OutputLog;
output_test = output_test(1:1000,:);

%subplot(2,1,1)
%stem(output_test(1:100,2)); axis tight;
%subplot(2,1,2)
%Rx Signal
%plot(output_test(1:100,1)); axis tight;

rx_test = output_test(:,1);
rx_average_test = mean(rx_test);
rx_test = rx_test - rx_average_test;

t = (0:Ts:Ts*1000-Ts)';
[A,B,C,D] = ssdata(sys_train);
sys = ss(A,B,C,D,Ts);
[y,t,x] = lsim(sys,prbs_test(:,2),t);

% figure()
subplot(1,1,1)
interval = 101:200;
plot(t(interval),rx_test(interval),t(interval),y(interval)); axis tight;
legend('sample','model')

%%
% this cell is to test against the randon binary sequence

% ONLY uncomment if you want to run the simulink model
tg.start; pause(0.001);

% Tx Signal
output = tg.OutputLog;
output = output(1:1000,:);

tx = output(:,2);
rx = output(:,1);
rx_average = mean(rx);
rx = rx - rx_average;

[A,B,C,D] = ssdata(sys_train);
sys = ss(A,B,C,D,Ts);
[y,t,x] = lsim(sys,tx,t);

interval = 1:100;
plot(t(interval),rx(interval),t(interval),y(interval)); axis tight;
legend('sample','model')