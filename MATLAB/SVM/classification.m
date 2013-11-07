%% Setup indexes to examine
%% select the data points to get
%%
clc;
%data_i = randperm(21);
%train_i = data_i(1:floor(length(data_i))/2);
%test_i = data_i((floor(length(data_i)/2)+1):end);
s_norm = zeros(2,1);
% index filter
train_i = 1:57;
for i = train_i
    basePath = 'C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLogOrder3\AL\';
    [sys_train, OutputLog_a, x_a, y_a] = getData(basePath,i);

    % get singular and/or norm values
    s_norm(i) = norm(sys_train); % id model norm
end
[s_norm_sorted, H2Norm_I] = sort(s_norm);
    
%norm_limit = 0.6750;
%norm_lower_limit = 0;
%norm_lower_limit = 0.685; % Determined through examination of the data
norm_lower_limit = 0.70;
norm_upper_limit = 0.730;
%norm_upper_limit = inf;
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
    basePath = 'C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLogOrder3\AL\';
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
    xtemp2 = [xtemp2, addedFeature];
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
class_label = 0:1:7;
xtemp2 = [];
ytemp2 = [];
for j = 1:length(class_label)
   I = find(ytemp == class_label(j));
   xtemp2 = [xtemp2; xtemp(I,:)];
   ytemp2 = [ytemp2; ytemp(I)];
end
xtemp = xtemp2;
ytemp = ytemp2;

%split data
P = cvpartition(ytemp,'Holdout',0.10);
Ymat_train = ytemp(P.training);
Ymat_test = ytemp(P.test);
Xmat_train = xtemp(P.training,:);
Xmat_test = xtemp(P.test,:);
%% SVM 1vAll -> binary
%% 
y = [];
% 0,1 for closer or further
for i = 1:length(class_label)
    GvAll = (Ymat_train == class_label(i));
    svmStruct = svmtrain(Xmat_train, GvAll,'kernel_function','rbf','rbf_sigma',0.5,'method','QP');
    svmTestStruct(i) = svmStruct;
end

clear results;
for i = 1:length(Ymat_test)
    for j = 1:length(class_label)
        r = svmclassify(svmTestStruct(j), Xmat_test(i,:),'showplot',true);
        results(i,j) = r;
    end
end
results = [Ymat_test, results];
results_old = results;

% SVM Drill Down
fuzzy_classify = zeros(2,1);
for i = 1:size(results,1)
    % if more than one positive hit
    if sum(results(i,2:end)) > 1
        % set the range of fuzzy results
        fuzzy_results = find(results(i,2:end));
        fuzzy_results = min(fuzzy_results):max(fuzzy_results);
        naive_avg = [];
        % SVM 1vAll Level: compare all fuzzy results
        for j = 2:length(fuzzy_results)
            label_1 = Ymat_train == class_label(fuzzy_results(j-1));
            label_2 = Ymat_train == class_label(fuzzy_results(j));
            % get classification for each individual sensor
            r_subset = [];
            index = 0;
            % SVM sensor level
            for k=1:3 % hard coded to 3 sensors
                Ymat_train_subset = Ymat_train(logical(label_1+label_2));
                Xmat_train_subset = Xmat_train(logical(label_1+label_2),[k,4]);
                svmStruct_subset = svmtrain(Xmat_train_subset, Ymat_train_subset,'kernel_function','polynomial','method','QP');

                Xmat_test_subset = Xmat_test(i,[k,4]);
                index = index + 1;
                r_subset(index) = svmclassify(svmStruct_subset,Xmat_test_subset);
            end
            %weight_snr = [0.2;0.2;0.6];
            naive_avg(j-1) = mean(r_subset); % Test
            %naive_avg(j-1) = mean(r_subset); % Test
            %naive_avg(j-1) = max(r_subset);
        end
        results(i,2:end) = 0;
        results(i,int8(mean(naive_avg))+2) = 1;
        fuzzy_classify(i) = mean(naive_avg);
    else
        fuzzy_results = find(results(i,2:end));
        if ~isempty(fuzzy_results)
            fuzzy_classify(i) = class_label(fuzzy_results);
        end
    end
end
fuzzy_classify = [Ymat_test,fuzzy_classify];
%% SVM 1vAll -> (subset) 1vAll
%% 
y = [];
% 0,1 for closer or further
for i = 1:length(class_label)
    GvAll = (Ymat_train == class_label(i));
    svmStruct = svmtrain(Xmat_train, GvAll,'kernel_function','rbf','rbf_sigma',1,'method','QP');
    svmTestStruct(i) = svmStruct;
end

clear results;
for i = 1:length(Ymat_test)
    for j = 1:length(class_label)
        r = svmclassify(svmTestStruct(j), Xmat_test(i,:),'showplot',true);
        results(i,j) = r;
    end
end
results = [Ymat_test, results];
results_old = results;
% SVM Drill Down
fuzzy_classify = zeros(size(results,1),1);
for i = 1:size(results,1)
%for i = 73:77
    % if more than one positive hit
    if sum(results(i,2:end)) > 1
        % set the range of fuzzy results
        fuzzy_results = find(results(i,2:end));
        naive_acc = [];
        % SVM 1vAll Level: compare all fuzzy results
        label = [];
        Ymat_train_subset = [];
        Xmat_train_subset = [];
        for j = 1:length(fuzzy_results)
           label = Ymat_train == class_label(fuzzy_results(j));
           Ymat_train_subset = [Ymat_train_subset; Ymat_train(label)];
           Xmat_train_subset = [Xmat_train_subset; Xmat_train(label,:)];
        end
        for j = 1:length(fuzzy_results)
            GvAll = (Ymat_train_subset == class_label(fuzzy_results(j)));
            % get classification for each individual sensor
            r_subset = [];
            index = 0;
            % SVM sensor level
            for k=1:3 % hard coded to 3 sensors
                Xmat_train_subset_snr = Xmat_train_subset(:,[k,4]);
                svmStruct_subset = svmtrain(Xmat_train_subset_snr, GvAll,'kernel_function','polynomial','method','QP');

                Xmat_test_subset = Xmat_test(i,[k,4]);
                index = index + 1;
                r_subset(index) = svmclassify(svmStruct_subset,Xmat_test_subset).*class_label(fuzzy_results(j));
            end
            nonzero = find(r_subset);
            naive_acc = [naive_acc, r_subset(nonzero)];
            %naive_avg(j) = max(r_subset)
        end
        results(i,2:end) = 0;
        results(i,int8(mean(naive_acc))+2) = 1;
        fuzzy_classify(i) = mean(naive_acc);
    else
        fuzzy_results = find(results(i,2:end));
        if ~isempty(fuzzy_results)
            fuzzy_classify(i) = class_label(fuzzy_results);
        end
    end
end
fuzzy_classify = [Ymat_test,fuzzy_classify]

%% SVM Light by Joachim
%%
class_label = [0,1,2,3,4]'; % Specify the distance labels for the 
y = [];
% 0,1 for closer or further
clear svmTestStruct;

% autoscale data if required,
scaleData = [];
Xmat_train_a = [];
scaleData.shift = - mean(Xmat_train);
stdVals = std(Xmat_train);
scaleData.scaleFactor = 1./stdVals;
% leave zero-variance data unscaled:
scaleData.scaleFactor(~isfinite(scaleData.scaleFactor)) = 1;

% shift and scale columns of data matrix:
for c = 1:size(Xmat_train, 2)
    Xmat_train_a(:,c) = scaleData.scaleFactor(c) * ...
        (Xmat_train(:,c) +  scaleData.shift(c));
end


for i = 1:length(class_label)
    GvAll = (Ymat_train == class_label(i))*2 - 1;
    %equalize the number of positive and negative examples
    trueI = find(GvAll==1);
    falseI = find(GvAll==-1);
    randI = randperm(length(falseI));
    falseI = falseI(randI(1:length(trueI)));
    GvAll = GvAll([trueI;falseI]);
    Xmat_train_a_equal = Xmat_train_a([trueI;falseI],:);
    
    svmStruct = svmlearn(Xmat_train_a_equal, GvAll,'-t 2 -g 0.7 -b 1 -e 0.0000000001');
    svmTestStruct(i) = svmStruct;
end

clear results;
% autoscale data if required,
scaleData = [];
Xmat_test_a = [];
scaleData.shift = - mean(Xmat_train);
stdVals = std(Xmat_train);
scaleData.scaleFactor = 1./stdVals;
% leave zero-variance data unscaled:
scaleData.scaleFactor(~isfinite(scaleData.scaleFactor)) = 1;

% shift and scale columns of data matrix:
for c = 1:size(Xmat_test, 2)
    Xmat_test_a(:,c) = scaleData.scaleFactor(c) * ...
        (Xmat_test(:,c) +  scaleData.shift(c));
end


for i = 1:length(Ymat_test)
    for j = 1:length(class_label)
        if Ymat_test(i) == class_label(j)
            [e,r] = svmLclassify(Xmat_test_a(i,:), 1,svmTestStruct(j));
        else
            [e,r] = svmLclassify(Xmat_test_a(i,:), -1,svmTestStruct(j));  
        end
        results(i,j) = r;
    end
end
results = [Ymat_test, results];
results(:,2:end) = results(:,2:end) > 0
%% examine the data
scatter(Ymat,Xmat(:,4))