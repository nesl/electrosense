%%
% global parameters
range = 1:60;
if ispc
basePath = 'C:\Users\newton\Dropbox\NESL_Software\electrosense\DATA\ModelWeekLogOrder3\AL\';
txTrainPath = 'C:\Users\newton\Dropbox\NESL_Software\electrosense\DATA\ModelWeekLogOrder3\tx_train.mat';
transSigPath = 'C:\Users\newton\Dropbox\NESL_Software\electrosense\DATA\ModelWeekLogOrder3\trans_signal.mat';
else
basePath = '/Users/newton/Dropbox/NESL_Software/electrosense/DATA/ModelWeekLogOrder3/AL/';
txTrainPath = '/Users/newton/Dropbox/NESL_Software/electrosense/DATA/ModelWeekLogOrder3/tx_train.mat';
transSigPath = '/Users/newton/Dropbox/NESL_Software/electrosense/DATA/ModelWeekLogOrder3/trans_signal.mat';
end
load(transSigPath);
load(txTrainPath);

% exclude & split
exclude = [1 2 3 5 6 7 8 9 12 13 15 23 25 27 29 30 31 32 33 37 40 43 46 47 48 49 54 55 56 57 59];
% 9 37 54 33 55 5 48 43 40 13
all = 1:60;
all(exclude) = [];
IR = randperm(length(all),5);
test = all(IR);
train = 1:60;
train([IR,exclude]) = [];

range = all;
%%
% vectorize the raw prbs
vecRxTrain = [];
vecTxTrain = [];
arrayOutputLog = [];
for sets=range
    % retrieve
    [sys_train,OutputLog,x,y,rx_train] = getData(basePath, sets);
    % remove mean
    rx_train = rx_train - kron(ones(size(rx_train,1),1), mean(rx_train));
    % cat rx_train & tx_train
    vecRxTrain = [vecRxTrain; rx_train];
    vecTxTrain = [vecTxTrain; tx_train];
    arrayOutputLog = [arrayOutputLog, OutputLog'];
end

% estimate state space model
Ts_out = 1e-4;
data_train = iddata(vecRxTrain, vecTxTrain, Ts_out); 
[sys_train, x0_train] = n4sid(data_train,'best');
%%
% process data through Kalman filter
%range = [2,5,10,14];
%range = [2,5,14,20];
%range = [4,9]; % these are indexes in vector 'range'
range = 9;
vecX5 = {};
vecY5 = {};
index = 0;
for i=range
    vecX = [];
    vecY = [];
    index = index + 1;
    
    OutputLog_Data = arrayOutputLog(:,i);
    [x,y] = fKalmanScriptTV(sys_train,OutputLog_Data,trans_signal);
    xmean = zeros(2,3);
    ymean = zeros(2,1);
    % average stable KF results
    for j=1:39
       starti = 1 + (j-1)*30;
       endi = starti + 29;
       xmean(j,:) = mean(x(starti:endi,:));
       ymean(j) = mean(y(starti:endi));
    end
    vecX = [vecX; xmean];
    vecY = [vecY; ymean];
    
    % transform data to linearize it
    vecX = (1./vecX).^(1/3);

    % filter out specific data points
    class_label = 0:1:7;
    vecXtemp = [];
    vecYtemp = [];
    for j = 1:length(class_label)
       I = find(vecY == class_label(j));
       vecXtemp = [vecXtemp; vecX(I,:)];
       vecYtemp = [vecYtemp; vecY(I)];
    end
    
    vecX5{index} = vecXtemp;
    vecY5{index} = vecYtemp;
end

% Display KF results
for i=1:index
    scatter(vecY5{i},vecX5{i}(:,1),100,'filled');
    hold on;
    scatter(vecY5{i},vecX5{i}(:,2),100,'filled');
    scatter(vecY5{i},vecX5{i}(:,3),100,'filled');
    hold off;
%     if i==1
%         hold on;
%     elseif i==index
%         hold off;
%     end
end
axis tight;
legend('1','2','3')
xlabel('Distance from target (inches)','fontsize',14);
ylabel('Kalman filter output','fontsize',14);