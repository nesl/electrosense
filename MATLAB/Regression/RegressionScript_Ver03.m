%% Train Regressoin Model using historical data
% Allows for flexible selection of data
%% select the data points to get
%%
%clc;
%data_i = randperm(21);
%train_i = data_i(1:floor(length(data_i))/2);
%test_i = data_i((floor(length(data_i)/2)+1):end);
s_norm = zeros(2,1);
% index filter
train_i = 1:57;
for i = train_i
    %basePath = 'C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLogOrder3\AL\';
    basePath = '/Users/newton/Dropbox/NESL_Software/electrosense/DATA/ModelWeekLogOrder3/AL/';
    [sys_train, OutputLog_a, x_a, y_a] = getData(basePath,i);

    % get singular and/or norm values
    s_norm(i) = norm(sys_train); % id model norm
end
[s_norm_sorted, H2Norm_I] = sort(s_norm);
    
%norm_limit = 0.6750;
norm_lower_limit = 0;
%norm_lower_limit = 0.685; % Determined through examination of the data
%norm_lower_limit = 0.71;
%norm_upper_limit = 0.720;
norm_upper_limit = inf;
I1 = s_norm_sorted > norm_lower_limit;
I2 = s_norm_sorted < norm_upper_limit;
I = find(I1 & I2);

% set indexes here
train_i = H2Norm_I(I);
%rand_i = randperm(length(I));
%train_i = H2Norm_I(I(rand_i(1:floor(length(I)/2))));
%test_i = H2Norm_I(I(rand_i(ceil(length(I)/2):end)));
%% Get data
%%
Anorm = zeros(2,1);
Snorm = zeros(2,1);
SnormINF = zeros(2,1);
Amat = {};
Xmat = [];
Ymat = [];
b4tharray = [];
bquadarray = [];
AnormArray = [];
xtemp = [];
ytemp = [];
for i = 1:length(train_i)  
    %basePath = 'C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLogOrder3\AL\';
    %basePath = 'C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\MURI\TestDistance\Update_flaw_3\Order3\';
    basePath = '/Users/newton/AeroFS/NESL_Software/electrosense/DATA/ModelWeekLogOrder3/AL/';
    [sys_train, OutputLog, x, y] = getData(basePath,train_i(i));
   
    % get singular and/or norm values
    svd_values = svd(sys_train.A);
    Snorm(i) = norm(sys_train);
    SnormINF(i) = norm(sys_train,inf);
    
    % include averaging to estimated values
    xtemp2 = [];
    for j = 1:size(x,1)/30
       starti = 1 + (j-1)*30;
       endi = starti + 29;
       xtemp2(j,:) = mean(x(starti:endi,:));
    end
    addedFeature = kron(ones(size(xtemp2,1),1),Snorm(i));
    %xtemp2 = [xtemp2, addedFeature];
    xtemp = [xtemp; xtemp2];

    % include averaging to estimate values
    ytemp2 = [];
    for j = 1:size(y,1)/30
      starti = 1 + (j-1)*30;
      endi = starti + 29;
      ytemp2(j,:) = mean(y(starti:endi,:));
    end
    ytemp = [ytemp; ytemp2];
end

% include a subset of the distances measured
class_label = 4:1:7;
xtemp2 = [];
ytemp2 = [];
for j = 1:length(class_label)
   I = find(ytemp == class_label(j));
   xtemp2 = [xtemp2; xtemp(I,:)];
   ytemp2 = [ytemp2; ytemp(I)];
end
xtemp = xtemp2;
ytemp = ytemp2;
%% for distances 4 to 7 inches only
xtemp = exp(xtemp.*kron(ones(size(xtemp,1),1),[1000,500,5000]));

%%
%Ymat_train = ytemp;
%Ymat_test = ytemp;
%Xmat_train = xtemp;
%Xmat_test = xtemp;

%split data
P = cvpartition(ytemp,'Holdout',0.10);
Ymat_train = ytemp(P.training);
Ymat_test = ytemp(P.test);
Xmat_train = xtemp(P.training,:);
Xmat_test = xtemp(P.test,:);
%% Autoscale
scaleData = [];
scaleData.shift = -mean(Xmat_train);
stdVal = std(Xmat_train);
scaleData.scaleFactor = 1./stdVal;
scaleData.scaleFactor(~isfinite(scaleData.scaleFactor)) = 1;
Xmat_train_a = [];
for i=1:size(Xmat_train,2)
    Xmat_train_a(:,i) = scaleData.scaleFactor(i)*(Xmat_train(:,i) + scaleData.shift(i));
end
%% Regress Train
Y = Ymat_train;
X = [ ones(size(Xmat_train_a,1),1), Xmat_train_a, Xmat_train_a.^2, Xmat_train_a.^3, Xmat_train_a.^4];
%X = [ ones(size(Xmat_train_a,1),1), abs(log(Xmat_train_a)), abs(log(Xmat_train_a)).^2];
[b,bint,r,rint,stats] = regress(Y,X);
%% Regress Test
%scaleData = [];
%scaleData.shift = -mean(Xmat_train);
%stdVal = std(Xmat_train);
%scaleData.scaleFactor = 1./stdVal;
%scaleData.scaleFactor(~isfinite(scaleData.scaleFactor)) = 1;

% include a subset of the distances measured
class_label = 0:1:3;
Xmat_temp = [];
Ymat_temp = [];
for j = 1:length(class_label)
   I = find(Ymat_test == class_label(j));
   Xmat_temp = [Xmat_temp; Xmat_test(I,:)];
   Ymat_temp = [Ymat_temp; Ymat_test(I)];
end
Xmat_test_2 = Xmat_temp;
Ymat_test_2 = Ymat_temp;

%keep_i = ones(size(Xmat_test_2,1),1);
%for i=1:size(Xmat_test_2,1)
%   if  Xmat_test_2(i,1) > (mean(Xmat_train(:,1)) + std(Xmat_train(:,1)))
%       keep_i(i) = 0;
%   end
%end
%Xmat_test_2 = Xmat_test_2(logical(keep_i),:);
%Ymat_test_2 = Ymat_test_2(logical(keep_i),:);

Xmat_test_a = [];
for i=1:size(Xmat_test_2,2)
    Xmat_test_a(:,i) = scaleData.scaleFactor(i)*(Xmat_test_2(:,i) + scaleData.shift(i));
end
X = [ones(size(Xmat_test_a,1),1), Xmat_test_a, Xmat_test_a.^2, Xmat_test_a.^3,Xmat_test_a.^4];
%X = [ ones(size(Xmat_test_a,1),1), abs(log(Xmat_test_a)), abs(log(Xmat_train_a)).^2];
Y = X*b;
%rid = size(Ymat_test_2,1);
%rid = rid(rid~=6);
%Ymat_test_2 = Ymat_test_2(rid,:);
%Y = Y(rid,:);

scatter(Ymat_test_2, Y,90,'filled');
%axis([3.5,7.5,3.5,7.5])
axis([-0.5,3.5,-0.50,3.5])
%set(gca,'fontsize',20)
%set(gca,'YTick',[0,1,2,3])