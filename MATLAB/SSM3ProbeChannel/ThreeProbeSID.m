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
% Valdecal       |----|--------                    |          |    |
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

ValAmpli = 5;  %: Magnitude
ValDecal = 0;  %: Add-on DC component

ValLgReg = 10;  %: Register length (# of cells)
ValDivi = 1;   %: Frequency divider (pulse length multiplier)

Nsamp = 1000;     %: Number of samples

prbs = create_prbs(ValUinit, ValAmpli, ValDecal, ValLgReg, ValDivi, Nsamp, Tappli)';
Ts = 1e-3;
t = (0:Ts:Ts*500-Ts)';
prbs_train = [t, prbs(1:500)];
prbs_test = [t, prbs(501:1000)];
stem(prbs(1:500));
%% Build Model

% freq = 500 Hz
sec = 1;
Ts_out = 1e-4; % Ts_out is the received sampling frequency
sampled_length = Nsamp/2*Ts/1e-4;

% ONLY uncomment if you want to run the simulink model
rtwbuild(gcs);
tg.start; pause(2);
rx_train = tg.OutputLog(1:sampled_length,1:3); % there is an unknown zero value for the first element
rx_train_b = rx_train;
tx_train = tg.OutputLog(1:sampled_length,4);

% take out any DC bias
rx_average_train = mean(rx_train,1)';
for i=1:size(rx_train,2);
    rx_train(:,i) = rx_train(:,i) - ones(sampled_length,1).*rx_average_train(i);
end

data_train = iddata(rx_train, tx_train, Ts_out); 
% get state-space model using subspace method
[sys_train, x0_train] = n4sid(data_train,3); % 'best' extimates the order
%% Test model (manual)
% rebuild simulink model

% ONLY uncomment if you want to run the simulink model
rtwbuild(gcs);
tg.start; pause(3);
rx_test = tg.OutputLog(1:sampled_length,1:3);
tx_test = tg.OutputLog(1:sampled_length,4);


rx_average_test = mean(rx_test,1);
for i=1:3
    rx_test(:,i) = rx_test(:,i) - ones(sampled_length,1).*rx_average_test(i);
end

t = (0:Ts_out:Ts_out*sampled_length-Ts_out)';
[A,B,C,D] = ssdata(sys_train);
sys = ss(A,B,C,D,Ts_out);
[y,t,x] = lsim(sys,tx_test,t);
err = norm(y-rx_test);
%%
% Plot the signals received signal and the model side by side
% figure()
% subplot(1,1,1)
interval = 1:500;
plot(t(interval),rx_test(interval),t(interval),y(interval)); axis tight;
legend('sample','model')

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
%% Run Whiteness and Independence test

% freq = 500 Hz
Ts_out = 1e-4; % Ts_out is the received sampling frequency
sampled_length = Nsamp/2*Ts/1e-4;

% ONLY uncomment if you want to run the simulink model
% Don't forget to change to testing signal
rtwbuild(gcs);
tg.start; pause(2);
rx_test = tg.OutputLog(1:sampled_length,1:3); % there is an unknown zero value for the first element
rx_test_b = rx_test; % rx_train with the DC bias
tx_test = tg.OutputLog(1:sampled_length,4);

% take out any DC bias
rx_average_test = mean(rx_test,1)';
for i=1:size(rx_test,2);
    rx_test(:,i) = rx_test(:,i) - ones(sampled_length,1).*rx_average_test(i);
end

data_test = iddata(rx_test, tx_test, Ts_out);
resid(sys_train,data_test,'corr',50);