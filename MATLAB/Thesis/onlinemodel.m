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

% vectorize the raw prbs
vecX = {};
vecY = {};
sys  = {};
arrayOutputLog = [];
sNorm = [];
for sets=range
    % retrieve
    [sys_train,OutputLog,x,y,rx_train] = getData(basePath, sets);
    xmean = zeros(2,3);
    ymean = zeros(2,1);
    for j=1:39
        starti = 1 + (j-1)*30;
        endi = starti + 29;
        xmean(j,:) = mean(x(starti:endi,:));
        ymean(j) = mean(y(starti:endi));
    end
    vecX{sets} = (1./xmean).^(1/3);
    vecY{sets} = ymean;
    sys{sets} = sys_train;
    
end

%%
% process data through Kalman filter
%range = [2,5,10,14];
%range = [2,5,14,20];
range = 20;
vecX5 = {};
vecY5 = {};
index = 0;
for i=range
    index = index + 1;

    % filter out specific data points
    class_label = 0:1:7;
    vecXtemp = [];
    vecYtemp = [];
    for j = 1:length(class_label)
       I = find(vecY{i} == class_label(j));
       vecXtemp = [vecXtemp; vecX{i}(I,:)];
       vecYtemp = [vecYtemp; vecY{i}(I)];
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
xlabel('Distance from target (inches)','fontsize',14);
ylabel('Kalman filter output','fontsize',14);