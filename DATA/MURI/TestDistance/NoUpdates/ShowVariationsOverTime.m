load x_01;
load x_02;
load x_03;
load x_04;
load y_01;
load y_02;
load y_03; 
load y_04;
%%
load sys_train_01;
load sys_train_02;
load sys_train_03;
load sys_train_04;
load OutputLog_01;
load OutputLog_02;
load OutputLog_03;
load OutputLog_04;
%%
x_cell = {};
x_cell{1} = x_01;
x_cell{2} = x_02;
x_cell{3} = x_03;
x_cell{4} = x_04;
%%
% use update_flaw3 data
% start with 2 because one has errors
x = x_01(1:480,:);
y = y_01(1:480,:);
X4th = [ones(size(x,1),1) x x.^2 x.^3 x.^4];
[b4th bint4th,r,rint,stats] = regress(y,X4th);
results4th = X4th*b4th;
scatter(y,results4th)
%%
results_mean = [];
y_mean = [];
for j=2:4
    x = x_cell{j};
    X4th = [ones(size(x,1),1) x x.^2 x.^3 x.^4];
    results4th = X4th*b4th;
    for i=1:15
        starti = 1 + (i-1)*30;
        endi = starti + 29;
        results_mean(i,j) = mean(results4th(starti:endi));
        y_mean(i) = y(starti);
    end
end
scatter(y_mean,results_mean(:,4),100,'filled')
%%
y_mean_temp = [];
results_mean_temp = [];
for i=0:9
   I = find(y_mean==i);
   y_mean_temp = [y_mean_temp; y_mean(I)];
   results_mean_temp = [results_mean_temp; results_mean(I,:)];
end
%%
for i=2:4
    if i==4
        hold on;
    end
    scatter(y_mean_temp,results_mean_temp(:,i),100,'filled');
end
blah = 0:7
scatter(blah,blah,100,'filled')
hold off;
legend('~30 mins after','~60 mins after')
%xlabel('Distance from target (inches)')
%ylabel('Predictions from trained regression');
title('Test prediction limts');
%title('Test prediction accuracy over time');
%h=legend('Nmax=8','Nmax=10','Nmax=12','Nmax=14');
%rect = [0.65, 0.13, .125, .125];
%set(h, 'Position', rect)
axis([0,7.5,0,7.5])