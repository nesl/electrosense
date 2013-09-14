%% Get random data points
% Threshold id model norm 0.6750

clc;
%data_i = randperm(21);
%train_i = data_i(1:floor(length(data_i))/2);
%test_i = data_i((floor(length(data_i)/2)+1):end);
train_i = 1:30;
Anorm = zeros(2,1);
s_norm = zeros(2,1);
Amat = {};
Xmat = {};
b4tharray = [];
bquadarray = [];
AnormArray = [];

% index filter
for i = train_i
    if ispc
    sys_train_str = ['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLog\',num2str(train_i(i),'%02d'),'\sys_train_',num2str(train_i(i),'%02d')];
    bquad_str = ['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLog\',num2str(train_i(i),'%02d'),'\bquad_',num2str(train_i(i),'%02d')];
    %b4th_str = ['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLog\',num2str(train_i(i),'%02d'),'\b4th_',num2str(train_i(i),'%02d')];
    x_str = ['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLog\',num2str(train_i(i),'%02d'),'\x_',num2str(train_i(i),'%02d')];
    y_str = ['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLog\',num2str(train_i(i),'%02d'),'\y_',num2str(train_i(i),'%02d')];
    else   
    sys_train_str = ['/Users/newton/AeroFS/NESL_Software/electrosense/DATA/ModelWeekLog/',num2str(train_i(i),'%02d'),'/sys_train_',num2str(train_i(i),'%02d')];
    bquad_str = ['/Users/newton/AeroFS/NESL_Software/electrosense/DATA/ModelWeekLog/',num2str(train_i(i),'%02d'),'/bquad_',num2str(train_i(i),'%02d')];
    %b4th_str = ['/Users/newton/AeroFS/NESL_Software/electrosense/DATA/ModelWeekLog/',num2str(train_i(i),'%02d'),'/b4th_',num2str(train_i(i),'%02d')];
    x_str = ['/Users/newton/AeroFS/NESL_Software/electrosense/DATA/ModelWeekLog/',num2str(train_i(i),'%02d'),'/x_',num2str(train_i(i),'%02d')];
    y_str = ['/Users/newton/AeroFS/NESL_Software/electrosense/DATA/ModelWeekLog/',num2str(train_i(i),'%02d'),'/y_',num2str(train_i(i),'%02d')];
    end
   
   
   % get system A matrix
   A_temp = load(sys_train_str);
   A_fields = fieldnames(A_temp);
  
   % get singular and/or norm values
   s_norm(i) = norm(A_temp.(A_fields{1})); % id model norm
   [s_norm_sorted, H2Norm_I] = sort(s_norm);
end

%norm_limit = 0.6750;
%norm_limit = 0.7;
norm_limit = 0.8;

for i=1:length(H2Norm_I)
    if s_norm_sorted(i) > norm_limit;
        break; 
    end
end

% set index here
train_i = 1:30;

%rand_i = randperm(i);
%train_i = H2Norm_I(rand_i(1:floor(i/2)));
%test_i = H2Norm_I(rand_i(ceil(i/2):end));
%%
Anorm = zeros(2,1);
Amat = {};
Xmat = {};
b4tharray = [];
bquadarray = [];
AnormArray = [];
for i = 1:length(train_i)
    if ispc
        sys_train_str = ['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLog\',num2str(train_i(i),'%02d'),'\sys_train_',num2str(train_i(i),'%02d')];
        bquad_str = ['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLog\',num2str(train_i(i),'%02d'),'\bquad_',num2str(train_i(i),'%02d')];
        b4th_str = ['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLog\',num2str(train_i(i),'%02d'),'\b4th_',num2str(train_i(i),'%02d')];
        x_str = ['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLog\',num2str(train_i(i),'%02d'),'\x_',num2str(train_i(i),'%02d')];
        y_str = ['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLog\',num2str(train_i(i),'%02d'),'\y_',num2str(train_i(i),'%02d')];
    else   
        sys_train_str = ['/Users/newton/AeroFS/NESL_Software/electrosense/DATA/ModelWeekLog/',num2str(train_i(i),'%02d'),'/sys_train_',num2str(train_i(i),'%02d')];
        bquad_str = ['/Users/newton/AeroFS/NESL_Software/electrosense/DATA/ModelWeekLog/',num2str(train_i(i),'%02d'),'/bquad_',num2str(train_i(i),'%02d')];
        b4th_str = ['/Users/newton/AeroFS/NESL_Software/electrosense/DATA/ModelWeekLog/',num2str(train_i(i),'%02d'),'/b4th_',num2str(train_i(i),'%02d')];
        x_str = ['/Users/newton/AeroFS/NESL_Software/electrosense/DATA/ModelWeekLog/',num2str(train_i(i),'%02d'),'/x_',num2str(train_i(i),'%02d')];
        y_str = ['/Users/newton/AeroFS/NESL_Software/electrosense/DATA/ModelWeekLog/',num2str(train_i(i),'%02d'),'/y_',num2str(train_i(i),'%02d')];
    end
   
   
   % get system A matrix
   A_temp = load(sys_train_str);
   A_fields = fieldnames(A_temp);
   Sysmat{i} = A_temp.(A_fields{1}); % id model struct
   Amat{i} = A_temp.(A_fields{1}).A; % id model A matrix
   
   X_temp = load(x_str);
   X_fields = fieldnames(X_temp);
   %Xmat{i} = X_temp.(X_fields{1});
   
   % include averaging to estimated values
   xtemp = X_temp.(X_fields{1});
   xtemp2 = [];
   for j = 1:size(xtemp,1)/30
       starti = 1 + (j-1)*30;
       endi = starti + 29;
       xtemp2(j,:) = mean(xtemp(starti:endi,:));
   end
   Xmat{i} = xtemp2;
   
   Y_temp = load(y_str);
   Y_fields = fieldnames(Y_temp);
   %Ymat{i} = Y_temp.(Y_fields{1});
   
   % include averaging to estimate values
   ytemp = Y_temp.(Y_fields{1});
   ytemp2 = [];
   for j = 1:size(ytemp,1)/30
      starti = 1 + (j-1)*30;
      endi = starti + 29;
      ytemp2(j,:) = mean(ytemp(starti:endi,:));
   end
   Ymat{i} = ytemp2;
   
   bquad_temp = load(bquad_str);
   bquad_fields = fieldnames(bquad_temp);
   bquadarray(:,i) = bquad_temp.(bquad_fields{1});
   
   b4th_temp = load(b4th_str);
   b4th_fields = fieldnames(b4th_temp);
   b4tharray(:,index) = b4th_temp.(b4th_fields{1});
   
   % get singular and/or norm values
   svd_values = svd(A_temp.(A_fields{1}).A);
   s_norm = norm(A_temp.(A_fields{1})); % id model norm
   s_norm_inf = norm(A_temp.(A_fields{1}),inf);
   
  %Anorm(i) = svd_values(1);
   Anorm(i) = s_norm;
   
   %AnormArray(i,:) = [s_norm, s_norm_inf];
   AnormArray(i,:) = [svd_values(1), svd_values(2), svd_values(3), s_norm, s_norm_inf];
   %AnormArray(i,:) = [s_norm,s_norm_inf];
   
end

b4tharray = b4tharray'; % 4th order regression coeff
bquadarray = bquadarray'; % 2nd order regression coeff
DataCor = [Anorm, bquadarray];
[blah,I] = sort(DataCor(:,1),1);
DataCor = DataCor(I,:);

% No averaging 
b4tharrayTrain = b4tharray;
bquadarrayTrain = bquadarray;
AnormArrayTrain = AnormArray;

% REGRESSION START
% find regression parameters for distance regression parameter update.
stheta = [];
statsarray = zeros(2,1);
PolyArrayTrain = [ones(length(AnormArrayTrain),1), AnormArrayTrain,AnormArrayTrain.^2];
for i = 1:size(bquadarrayTrain,2)
    %[b, bint, r, rint, stats] = regress(b4tharrayTrain(:,i),PolyArrayTrain);
    [b, bint, r, rint, stats] = regress(bquadarrayTrain(:,i),PolyArrayTrain);
    statsarray(i) = stats(1);
    stheta(i,:) = b';
end
% REGRESSION END

% cross validate the results
PolyArray = [ones(length(AnormArray),1), AnormArray, AnormArray.^2]; % svd of id model A matrix
bAdj = stheta*PolyArray';
bAdj = bAdj';


error_sum = zeros(2,1);
error_std = zeros(2,1);
error_avg = zeros(2,1);
dist_hat_mean_error= zeros(2,1);
stats_r2 = zeros(2,1);
data_disthat = [];
for i = 1:size(bAdj,1)
    % x = [ones(length(Xmat{i}),1), Xmat{i}, Xmat{i}.^2, Xmat{i}.^3, Xmat{i}.^4];
    x = [ones(length(Xmat{i}),1), Xmat{i}, Xmat{i}.^2];
    dist_hat = x*bAdj(i,:)';
    diff = Ymat{i} - dist_hat;
    % STATISTICS
    ssreg = sum((dist_hat - mean(Ymat{i})).^2);
    ssres = sum((Ymat{i} - dist_hat).^2);
    sstot = sum((Ymat{i} - mean(Ymat{i})).^2);
    R2 = 1 - ssres/sstot;
    stats_r2(i) = R2;
    data_disthat(i,:) = dist_hat;
    
    error_avg(i) = mean(diff);
    error_std(i) = std(diff);
    error_sum(i) = sum(diff);
    dist_hat_mean_error(i) = mean(dist_hat) - mean(Ymat{i});
end

[AnormArray(:,1), error_avg, error_std];
%% Testing
Anorm = zeros(2,1);
Amat = {};
Xmat = {};
Ymat = {};
b4tharray = [];
bquadarray = [];
AnormArray = [];
for i=1:length(test_i)
    if ispc
    sys_train_str = ['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLog\',num2str(test_i(i),'%02d'),'\sys_train_',num2str(test_i(i),'%02d')];
    bquad_str = ['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLog\',num2str(test_i(i),'%02d'),'\bquad_',num2str(test_i(i),'%02d')];
    %b4th_str = ['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLog\',num2str(test_i(i),'%02d'),'\b4th_',num2str(test_i(i),'%02d')];
    x_str = ['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLog\',num2str(test_i(i),'%02d'),'\x_',num2str(test_i(i),'%02d')];
    y_str = ['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLog\',num2str(test_i(i),'%02d'),'\y_',num2str(test_i(i),'%02d')];
    else   
    sys_train_str = ['/Users/newton/AeroFS/NESL_Software/electrosense/DATA/ModelWeekLog/',num2str(test_i(i),'%02d'),'/sys_train_',num2str(test_i(i),'%02d')];
    bquad_str = ['/Users/newton/AeroFS/NESL_Software/electrosense/DATA/ModelWeekLog/',num2str(test_i(i),'%02d'),'/bquad_',num2str(test_i(i),'%02d')];
    %b4th_str = ['/Users/newton/AeroFS/NESL_Software/electrosense/DATA/ModelWeekLog/',num2str(test_i(i),'%02d'),'/b4th_',num2str(test_i(i),'%02d')];
    x_str = ['/Users/newton/AeroFS/NESL_Software/electrosense/DATA/ModelWeekLog/',num2str(test_i(i),'%02d'),'/x_',num2str(test_i(i),'%02d')];
    y_str = ['/Users/newton/AeroFS/NESL_Software/electrosense/DATA/ModelWeekLog/',num2str(test_i(i),'%02d'),'/y_',num2str(test_i(i),'%02d')];
    end
   
   
   % get system A matrix
   A_temp = load(sys_train_str);
   A_fields = fieldnames(A_temp);
   Amat{i} = A_temp.(A_fields{1}).A;
   
   X_temp = load(x_str);
   X_fields = fieldnames(X_temp);
   %Xmat{i} = X_temp.(X_fields{1});
   
   % include averaging to estimated values
   xtemp = X_temp.(X_fields{1});
   xtemp2 = [];
   for j = 1:size(xtemp,1)/30
       starti = 1 + (j-1)*30;
       endi = starti + 29;
       xtemp2(j,:) = mean(xtemp(starti:endi,:));
   end
   Xmat{i} = xtemp2;
   
   
   Y_temp = load(y_str);
   Y_fields = fieldnames(Y_temp);
   %Ymat{i} = Y_temp.(Y_fields{1});
   
   % include averaging to estimate values
   ytemp = Y_temp.(Y_fields{1});
   ytemp2 = [];
   for j = 1:size(ytemp,1)/30
      starti = 1 + (j-1)*30;
      endi = starti + 29;
      ytemp2(j,:) = mean(ytemp(starti:endi,:));
   end
   Ymat{i} = ytemp2;
   
   bquad_temp = load(bquad_str);
   bquad_fields = fieldnames(bquad_temp);
   bquadarray(:,i) = bquad_temp.(bquad_fields{1});
   
   %b4th_temp = load(b4th_str);
   %b4th_fields = fieldnames(b4th_temp);
   %b4tharray(:,index) = b4th_temp.(b4th_fields{1});
   
   % get singular values
   svd_values = svd(A_temp.(A_fields{1}).A);
   s_norm = norm(A_temp.(A_fields{1})); % id model norm
   s_norm_inf = norm(A_temp.(A_fields{1}),inf);
   
   %Anorm(i) = svd_values(1);
   Anorm(i) = s_norm;
   
   %AnormArray(index,:) = [s_norm, s_norm_inf];
   AnormArray(i,:) = [svd_values(1),svd_values(2),svd_values(3), s_norm, s_norm_inf];
   %AnormArray(index,:) = [svd_values(1),svd_values(2)];
end

bquadarray = bquadarray';
DataCor = [Anorm, bquadarray];
[blah,I] = sort(DataCor(:,1),1);
DataCor = DataCor(I,:);

% cross validate the results
PolyArray = [ones(size(AnormArray,1),1), AnormArray, AnormArray.^2];
bAdj = stheta*PolyArray';
bAdj = bAdj';
error_sum = zeros(2,1);
error_std = zeros(2,1);
error_avg = zeros(2,1);
dist_hat_mean_error= zeros(2,1);
stats_r2 = zeros(2,1);
data_disthat = [];

for i = 1:size(bAdj,1)
    % dimension adjusted to "b" in y = a + bx;
    % x = [ones(length(Xmat{i}),1), Xmat{i}, Xmat{i}.^2, Xmat{i}.^3, Xmat{i}.^4];
    x = [ones(length(Xmat{i}),1), Xmat{i}, Xmat{i}.^2];
    dist_hat = x*bAdj(i,:)';
    diff = Ymat{i} - dist_hat;
    
    % STATISTICS
    ssreg = sum((dist_hat - mean(Ymat{i})).^2);
    ssres = sum((Ymat{i} - dist_hat).^2);
    sstot = sum((Ymat{i} - mean(Ymat{i})).^2);
    R2 = 1 - ssres/sstot;
    stats_r2(i) = R2;
    data_disthat(i,:) = dist_hat;
    
    error_avg(i) = mean(diff);
    error_std(i) = std(diff);
    error_sum(i) = sum(diff);
    dist_hat_mean_error(i) = mean(dist_hat) - mean(Ymat{i});
end

[AnormArray(:,1), error_avg, error_std];   
%% visualize regression estimation
close all;
DataCorAdj = [Anorm, bAdj];
[blah,I] = sort(DataCorAdj(:,1),1);
DataCorAdj = DataCorAdj(I,:);

error = [];
plotindex = 0;
for i=2:7
    plotindex = plotindex + 1;
    subplot(2,3,plotindex)
    % mean left in
    plot(DataCorAdj(:,1),DataCorAdj(:,i),'-rs',DataCor(:,1),DataCor(:,i),'-b*')
    %scatter(DataCor(:,1),DataCor(:,i));
    % mean subtracted
    %plot(DataCorAdj(:,1),(DataCorAdj(:,i) - mean(DataCorAdj(:,i))),'-rs',DataCor(:,1),(DataCor(:,i) - mean(DataCor(:,i))),'-b*')
    %plot(DataCor(:,1),DataCor(:,i),'-b*')
    legend('predict','truth');
    xlabel(num2str(i));
end

figure();
plotindex = 0;
for i=1:8
    plotindex = plotindex + 1;
    subplot(4,4,plotindex);
    scatter(Ymat{i},data_disthat(i,:));
    axis([0,5,0,5]);
    grid on;
    xlabel(num2str(i));
end 