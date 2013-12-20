%% MLtest3 SVM
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
dfreq = zeros(2,1);
arrayOutputLog = [];
sNorm = zeros(2,1);
sPeak = zeros(2,1);
sFPeak = zeros(2,1);
vecMean = {};
vecVar = {};
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
    
    class_label = 0:1:7;
    vecXtemp = [];
    vecYtemp = [];
    for j = 1:length(class_label)
       I = find(ymean == class_label(j));
       vecXtemp = [vecXtemp; xmean(I,:)];
       vecYtemp = [vecYtemp; ymean(I)];
    end    
    xmean = vecXtemp;
    ymean = vecYtemp;
    
    vecX{sets} = (1./xmean).^(1/3);
    vecY{sets} = ymean;
    sys{sets} = sys_train;   
    vecMean{sets} = mean(vecX{sets},2);
    vecVar{sets} = var(vecX{sets},0,2);

    dampf = damp(ss(sys_train));
    dfreq(sets) = dampf(1);     
    sNorm(sets) = norm(sys_train);
    [peak, fpeak] = norm(sys_train,inf);
    sPeak(sets) = peak;
    sFPeak(sets) = fpeak;
end
%%
vx = [];
vy = [];
for i=train
    X = [vecX{i}, vecVar{i}, kron(ones(8,1), [sNorm(i), dfreq(i)])];
    %X = [vecX{i}, vecVar{i}];
    %X = [ones(8,1), vecX{i}, vecVar{i}, kron(ones(8,1), sNorm(i))];
    Y = vecY{i};
    vx = [vx; X];
    vy = [vy; Y];
end
I = randperm(length(vy));
vx = vx(I,:);
vy = vy(I);

vxt = [];
vyt = [];
for i=test
   X = [vecX{i}, vecVar{i}, kron(ones(8,1), [sNorm(i), dfreq(i)])];
   %X = [vecX{i}, vecVar{i}];
   %X = [ones(8,1), vecX{i}, vecVar{i}, kron(ones(8,1), sNorm(i))];
   Y = vecY{i};
   vxt = [vxt; X];
   vyt = [vyt; Y];
end

%% Choose Classifier Here
% train
for i = 1:length(class_label)
    GvAll = (vy == class_label(i));
    svmStruct = svmtrain(vx, GvAll,'kernel_function','rbf','rbf_sigma',0.5,'method','QP');
    %svmStruct = svmtrain(vx, GvAll,'kernel_function','linear','method','SMO');
    %svmStruct = svmtrain(vx, GvAll,'method','QP');
    svmTestStruct(i) = svmStruct;
end

% test
clear results;
clear yhat;
for i = 1:length(vyt)
    avg = [];
    for j = 1:length(class_label)
        r = svmclassify(svmTestStruct(j), vxt(i,:));
        results(i,j) = r;
        if r == 1;
            avg = [avg, (j-1)];
        end
    end
    yhat(i) = mean(avg);
end
yhat = yhat';
[vyt,results]
%% plot results
for i = 1:length(test)
    starti = 1 + (i-1)*8;
    endi = starti + 7;
    %scatter(vyt,yhat,100,'filled');
    scatter(vyt(starti:endi),yhat(starti:endi),100,'filled');
    if i == 1
        hold on;
    elseif i == length(test)
        hold off;
    end
end
axis([-1,8,-1,8])
xlabel('Distance from sensor (inches)','fontsize',14);
ylabel('Estimation of distance from target (inches)','fontsize',14);

%%stats
%% stats
RMSE = [];
for i=1:length(class_label)
   I = find(vyt == (i-1));
   RMSE(i) = sqrt(mean((yhat(I) - vyt(I)).^2));
   
end