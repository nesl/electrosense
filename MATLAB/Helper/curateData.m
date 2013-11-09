%% Curate Data
%%
kalMeanIndexZero = zeros(1,3);
kalMeanIndexOne = zeros(1,3);
snorm = [];
basePath =  'C:\Users\newton\Dropbox\NESL_Software\electrosense\DATA\ModelWeekLogOrder3\AL\';
for i=1:58
   [sys_train,OutputLog,x,y] = getData(basePath, i);
   snorm(i) = norm(sys_train);
   kalMeanIndexZero(i,:) = mean(x(1:30,:));
   kalMeanIndexOne(i,:) = mean(x(31:60,:));
end
%%
outlierMark12 = zeros(58,1);
outlierMark22 = zeros(58,1);
outlierMark32 = zeros(58,1);
mean1 = mean(kalMeanIndexZero(:,1));
std1 = std(kalMeanIndexZero(:,1));
mean2 = mean(kalMeanIndexZero(:,2));
std2 = std(kalMeanIndexZero(:,2));
mean3 = mean(kalMeanIndexZero(:,3));
std3 = std(kalMeanIndexZero(:,3));

for i=1:58
    if kalMeanIndexZero(i,1) > mean1 + 2*std1 || kalMeanIndexZero(i,1) < mean1 - 2*std1
       outlierMark12(i) = 1; 
    end
    if kalMeanIndexZero(i,2) > mean2 + 2*std2 || kalMeanIndexZero(i,2) < mean2 - 2*std2
       outlierMark22(i) = 1; 
    end
    if kalMeanIndexZero(i,3) > mean3 + 2*std3 || kalMeanIndexZero(i,3) < mean3 - 2*std3
       outlierMark32(i) = 1; 
    end
end
%%
outlierMark4 = zeros(58,1);
outlierMark5 = zeros(58,1);
outlierMark6 = zeros(58,1);
mean1 = mean(kalMeanIndexOne(:,1));
std1 = std(kalMeanIndexOne(:,1));
mean2 = mean(kalMeanIndexOne(:,2));
std2 = std(kalMeanIndexOne(:,2));
mean3 = mean(kalMeanIndexOne(:,3));
std3 = std(kalMeanIndexOne(:,3));

for i=1:58
    if kalMeanIndexOne(i,1) > mean1 + std1 || kalMeanIndexOne(i,1) < mean1 - std1
       outlierMark4(i) = 1; 
    end
    if kalMeanIndexOne(i,2) > mean2 + std2 || kalMeanIndexOne(i,2) < mean2 - std2
       outlierMark5(i) = 1; 
    end
    if kalMeanIndexOne(i,3) > mean3 + std3 || kalMeanIndexOne(i,3) < mean3 - std3
       outlierMark6(i) = 1; 
    end
end