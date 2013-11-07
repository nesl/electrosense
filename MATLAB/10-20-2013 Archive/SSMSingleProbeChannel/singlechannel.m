% What this script does
% This script is designed to measure the channel in a fixed position and
% build a model using n4sid. You have to move the sensor before running
% this script.

%%
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

% change simulink time to 0.1 sec
ValUinit = 0;  %: Initial steady state
Tappli = 0;    %: Application instant 

ValAmpli = 1;  %: Magnitude
ValDecal = 0;  %: Add-on DC component

ValLgReg = 10;  %: Register length (# of cells)
ValDivi = 1;   %: Frequency divider (pulse length multiplier)

Nsamp = 2000;     %: Number of samples

prbs = create_prbs(ValUinit, ValAmpli, ValDecal, ValLgReg, ValDivi, Nsamp, Tappli)';
Ts = 1e-4;
t = (0:Ts:Ts*1000-Ts)';
prbs_train = [t, prbs(1:1000)];
prbs_test = [t, prbs(1001:2000)];
stem(prbs(1:1000));

%%
% examine the step information to make sure the PRBS is valid
tg.start; pause(1);
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
rtwbuild(gcs);
tg.start; pause(1);
output = tg.OutputLog(1:1000,1)';

% Manual inspection
% subplot(2,1,1)
% Tx Signal
% stem(output(1:100,2)); axis tight;
% subplot(2,1,2)
% Rx Signal
% plot(output(1:100,1)); axis tight;

% take out any DC bias
rx_train = output;
rx_average_train = mean(rx_train);
rx_train = rx_train - ones(1,1000)*rx_average_train;

Ts = 1e-4;
data = iddata(rx_train', prbs_train(:,2), Ts); 
% get state-space model using subspace method
[sys_train,x0_train] = n4sid(data,'best'); % 'best' extimates the order
%% Test model (manual)
% rebuild simulink model

% ONLY uncomment if you want to run the simulink model
rtwbuild(gcs);
tg.start; pause(1);
output_test = tg.OutputLog;

% Tx Signal
%subplot(2,1,1)
%stem(output_test(1:100,2)); axis tight;
%subplot(2,1,2)
%Rx Signal
%plot(output_test(1:100,1)); axis tight;

rx_test = output_test(1:1000,1);
rx_average_test = mean(rx_test);
rx_test = rx_test - rx_average_test;

t = (0:Ts:Ts*1000-Ts)';
[A,B,C,D] = ssdata(sys_train);
sys = ss(A,B,C,D,Ts);
[y,t,x] = lsim(sys,output_test(1:1000,2),t);
err = norm(y-rx_test);

% Plot the signals received signal and the model side by side
% figure()
% subplot(1,1,1)
% interval = 101:200;
% plot(t(interval),rx_test(interval),t(interval),y(interval)); axis tight;
% legend('sample','model')

%% Test model (automated)
% Automated test to collect error drift
for i=1:10
    if strcmp(gcs,'UnWaterChannelProbe')
        % rebuild simulink model
        % gcs: get current simulink
        % rtwbuild: evokes simulink compilation
        rtwbuild(gcs);
        % ONLY uncomment if you want to run the simulink model
        tg.start; pause(1);
        output_test = tg.OutputLog;
        % remove DC value
        rx_test = output_test(1:1000,1);
        rx_average_test = mean(rx_test);
        rx_test = rx_test - overall_mean;
        % setup to run simulation
        t = (0:Ts:Ts*1000-Ts)';
        [A,B,C,D] = ssdata(sys_train);
        sys = ss(A,B,C,D,Ts);
        [y,t,x] = lsim(sys,output_test(1:1000,2),t);
        % get error between rx signal and model prediction
        err_signal(i) = norm(y-rx_test);
        err_mean(i) = norm(rx_average_train - rx_average_test);
    end
    pause(50);
end

subplot(2,1,1)
scatter(1:length(err_mean),err_mean); xlabel('time'); ylabel('norm of mean error');
subplot(2,1,2)
scatter(1:length(err_mean),err_signal); ylabel('norm of signal error');
%%
% this cell is to test against the random binary sequence

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