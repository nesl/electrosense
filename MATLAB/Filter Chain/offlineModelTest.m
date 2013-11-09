% Case 1
% Model of channel is estimated from a large data set of PRBS
% Large set of target distance data is processed through a Kalman filter
% and used to train an estimation function. The model isn't updated before
% each target distance measurement.
%%
% global parameters
range = 1:60;
basePath = 'C:\Users\newton\Dropbox\NESL_Software\electrosense\DATA\ModelWeekLogOrder3\AL\';
txTrainPath = 'C:\Users\newton\Dropbox\NESL_Software\electrosense\DATA\ModelWeekLogOrder3\tx_train.mat';
transSigPath = 'C:\Users\newton\Dropbox\NESL_Software\electrosense\DATA\ModelWeekLogOrder3\trans_signal.mat';
load(transSigPath);
load(txTrainPath);

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
vecX = [];
vecY = [];
for i=range
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
end

% transform data to linearize it
vecX = (1./vecX).^(1/3);

% filter out specific data points
class_label = 0:1:7;
vecXtemp = [];
vecYtemp = [];
for i = 1:length(class_label)
   I = find(vecY == class_label(i));
   vecXtemp = [vecXtemp; vecX(I,:)];
   vecYtemp = [vecYtemp; vecY(I)];
end
vecX = vecXtemp;
vecY = vecYtemp;

% fold data
setFold = 1:5;
cvp = {};
for i=setFold
    cvp{i,1} = cvpartition(vecY,'Holdout',0.10);
end
%%
% find regression coefficents
stats = [];
MSE = [];
Ytrain = [];
Ytest = [];
for i=setFold
    vecXtrain = vecX(cvp{i}.training);
    vecYtrain = vecY(cvp{i}.training);
    vecXtest = vecX(cvp{i}.test);
    vecYtest = vecY(cvp{i}.test);
    % autoscale
    scaleData = [];
    scaleData.shift = -mean(vecXtrain);
    stdVal = std(vecXtrain);
    scaleData.scaleFactor = 1./stdVal;
    scaleData.scaleFactor(~isfinite(scaleData.scaleFactor)) = 1;
    Xmat_train_a = [];
    for j=1:size(vecXtrain,2)
        vecXtrain(:,j) = scaleData.scaleFactor(j)*(vecXtrain(:,j) + scaleData.shift(j));
    end
    % train
    X = [ones(size(vecXtrain,1),1) vecXtrain];
    Y = vecYtrain;
    [b,bint,r,rint,stat] = regress(Y,X);
    Ytrain = [Ytrain, X*b];
    stats(i,1) = stat(1);
    % test
    for j=1:size(vecXtest,2)
        vecXtest(:,j) = scaleData.scaleFactor(j)*(vecXtest(:,j) + scaleData.shift(j));
    end
    X = [ones(size(vecXtest,1),1), vecXtest];
    Y = X*b;
    MSE(i,1) = mean((vecYtest - Y).^2);
    Ytest = [Ytest, Y];
end
%%
% plot
for i=setFold
    if i > 1
        hold on;
    end
    scatter(vecYtrain,Ytrain(:,i));
end
hold off;
%scatter(vecYtest ,Ytest);

axis tight;