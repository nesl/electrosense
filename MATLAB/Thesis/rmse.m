y = [0,1,2,3,4,5,6,7];
xle = [0.668 0.573 0.824 1.152 1.041 0.879 0.319 0.931];
xsvm = [0 0.223 0.224 0.316 0.387 0.584 0.224 0.741];
scatter(y,xle,100,'filled')
hold on;
scatter(y,xsvm,100,'filled');
hold off;
lg = legend('Linear Estimation','SVM Classifier');
set(lg, 'FontSize',14)
xlabel('Distance from target (inches)','FontSize',14);
ylabel('Root Mean Square Error','fontsize',14);
