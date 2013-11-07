%% This script is to explore the whether binning the data helps reduce the errors
%% Setup indexes to examine
%%
% Threshold id model norm 0.6750

clc;
%data_i = randperm(21);
%train_i = data_i(1:floor(length(data_i))/2);
%test_i = data_i((floor(length(data_i)/2)+1):end);
train_i = 1:50;
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
norm_limit = 0;
%norm_limit = 0.6750;
%norm_limit = 0.685;
%norm_limit = 0.8;

for i=1:length(H2Norm_I)
    if s_norm_sorted(i) > norm_limit;
        break; 
    end
end

% set indexes here
train_i = H2Norm_I(i:end);
s_norm_sorted = s_norm_sorted(i:end);
%test_i = 31:34;
%rand_i = randperm(i);
%train_i = H2Norm_I(rand_i(1:floor(i/2)));
%test_i = H2Norm_I(rand_i(ceil(i/2):end));
%% Get data
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
    %Xmat{i} = xtemp2; % averaged
    Xmat{i} = xtemp;  % no average

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
    %Ymat{i} = ytemp2;   % averaged
    Ymat{i} = ytemp;    % no average

    bquad_temp = load(bquad_str);
    bquad_fields = fieldnames(bquad_temp);
    bquadarray(:,i) = bquad_temp.(bquad_fields{1});

    b4th_temp = load(b4th_str);
    b4th_fields = fieldnames(b4th_temp);
    b4tharray(:,i) = b4th_temp.(b4th_fields{1});
   
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

bquadarray = bquadarray'; % 2nd order regression coeff
bquad_lookup = [Anorm, bquadarray];
[blah,I] = sort(bquad_lookup(:,1),1);
bquad_lookup = bquad_lookup(I,:);


%% TESTING
%%
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

% round off s_norm
% 3 sig figs
Anorm = round(Anorm.*1000)/1000;

bquadarray = bquadarray';
DataCor = [Anorm, bquadarray];
[blah,I] = sort(DataCor(:,1),1);
DataCor = DataCor(I,:);

error_sum = zeros(2,1);
error_std = zeros(2,1);
error_avg = zeros(2,1);
dist_hat_mean_error= zeros(2,1);
stats_r2 = zeros(2,1);
data_disthat = [];
r_interpol = [];
for i = 1:length(test_i)
    % Interpolate regression values
    for j = 1:size(bquad_lookup,1)
        if bquad_lookup(j,1) > Anorm(i)
            if j > 1
                r_interpol = bquad_lookup(j-1,2:end) + Anorm(i)*(bquad_lookup(j,2:end)-bquad_lookup(j-1,2:end))/(bquad_lookup(j,1)-bquad_lookup(j-1,1));
                break;
            else
                %error('test SI norm out of bounds: norm too small');
                r_interpol = bquad_lookup(j,2:end);
            end
        elseif j == size(bquad_lookup,1);
            %error('test SI norm out of bounds: norm too big');
            r_interpol = bquad_lookup(j,2:end);
        end
    end
    
    display(j)
    % dimension adjusted to "b" in y = a + bx;
    x = [ones(length(Xmat{i}),1), Xmat{i}, Xmat{i}.^2];
    dist_hat = x*r_interpol';
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
%% Visualization
%%
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
%% 
Xclust = [];
for i=1:length(Xmat)
   Xclust = [Xclust; mean(Xmat{i}(1:30,:))]; 
end
Xclust2 = [];
for i=1:length(Xmat)
   Xclust2 = [Xclust2; mean(Xmat{i}(61:90,:))];
end
Xclust3 = [];
for i = 1:length(Xmat)
    Xclust3 = [Xclust3; mean(Xmat{i}(121:150,:))];
end
Xclust4 = [];
for i = 1:length(Xmat)
   Xclust4 = [Xclust4; mean(Xmat{i}(211:240,:))]; 
end

scatter(Xclust(:,2),s_norm_sorted)
xlabel('SI norm');ylabel('sensor 2');zlabel('SI norm')
hold on;
scatter(Xclust2(:,2),s_norm_sorted)
scatter(Xclust3(:,2),s_norm_sorted)
scatter(Xclust4(:,2),s_norm_sorted);
hold off;
legend('0 in','1 in','2 in','3 in')