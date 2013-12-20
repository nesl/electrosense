%% MLtest analysis
%%
% global parameters
%range = 1:60;
range = 60;
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
dfreq = zeros(2,1);
arrayOutputLog = [];
sNorm = zeros(2,1);
sPeak = zeros(2,1);
sFPeak = zeros(2,1);
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
    dampf = damp(ss(sys_train));
    dfreq(sets) = dampf(1);
    
    sNorm(sets) = norm(sys_train);
    [peak, fpeak] = norm(sys_train,inf);
    sPeak(sets) = peak;
    sFPeak(sets) = fpeak;
end
%% sort h2 norm

[sNormSorted, H2NormI] = sort(sNorm);

%%

[sFPeakSorted, sFPeakI] = sort(sFPeak(range));
low = 1.5e4;
high = 1.8e4;
I1 = sFPeakSorted > low;
I2 = sFPeakSorted < high;
I = find(I1 & I2);

blah = range(sFPeakI(I));
    
%% Set norm limits
    
%norm_limit = 0.6750;
%norm_lower_limit = 0;
%norm_lower_limit = 0.685; % Determined through examination of the data
norm_lower_limit = 0.7
%norm_lower_limit = 0.71;
%norm_lower_limit = 1.6e4;

norm_upper_limit = 0.715;
%norm_upper_limit = 0.720;
%norm_upper_limit = inf;
%norm_upper_limit = 1.62e4;

I1 = sNormSorted > norm_lower_limit;
I2 = sNormSorted < norm_upper_limit;
I = find(I1 & I2);

% set indexes here
range = H2NormI(I);

%%
% process data through Kalman filter
vecX5 = {};
vecY5 = {};
index = 0;
for i = 60
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
figure(1);
for i=1:index
    scatter(vecY5{i},vecX5{i}(:,1),100,'filled');
    %scatter(vecY5{i},vecX5{i}(:,2),100,'filled');
    %scatter(vecY5{i},vecX5{i}(:,3),100,'filled');
    if i==1
        hold on;
    elseif i==index
        hold off;
    end
end
%legend(num2str(range(1)), ...
%num2str(range(2)), ... 
%num2str(range(3)), ...
%num2str(range(4)), ...
%num2str(range(5)), ...
%num2str(range(6)) )
legend('1','2','3','4','5','6','7','8','9','10');
axis tight;
xlabel('Distance from target (inches)','fontsize',14);
ylabel('Kalman filter output w3(d)','fontsize',14);

%%
% process data through Kalman filter
vecX5 = {};
vecY5 = {};
index = 0;
for i = blah'
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
vecX5Norm = {};
for i=1:index
    for j=1:8
        vecX5Norm{i}(j) = norm(vecX5{i}(j,:));
    end
end

vecMean = {};
vecVar = {};
for i=1:index
    vecMean{i} = mean(vecX5{i},2);
    vecVar{i} = var(vecX5{i},0,2);
end


figure(2);
for i=1:index
    scatter(vecY5{i},vecMean{i},100,'filled');
    if i==1
        hold on;
    elseif i==index
        hold off;
    end
end

figure(3);
for i=1:index
    %scatter(vecY5{i},vecX5{i}(:,1)./vecVar{i},100,'filled');
    %scatter(vecY5{i},vecVar{i}./vecX5{i}(:,1),100,'filled');
    scatter(vecY5{i}, vecX5Norm{i},100,'filled');
    if i==1
        hold on;
    elseif i==index
        hold off;
    end
end