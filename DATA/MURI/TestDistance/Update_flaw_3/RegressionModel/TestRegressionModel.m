%% Test regression model
%% load model
load b;
load scaleData;
%%
Y = [];
Snorm = [];
for i=1:4
    sys_train_str = ['sys_train_',num2str(i,'%02d')];
    x_str = ['x_',num2str(i,'%02d')];
    y_str = ['y_',num2str(i,'%02d')];
    
    % get SID A matrix
    A_temp = load(sys_train_str);
    A_fields = fieldnames(A_temp);
    sys_train = A_temp.(A_fields{1});
    
    % get singular and/or norm values
    Snorm(i) = norm(sys_train);

    x_temp = load(x_str);
    x_fields = fieldnames(x_temp);
    x = x_temp.(x_fields{1});
    x = [x, kron(ones(size(x,1),1), Snorm(i))];
    
    y_temp = load(y_str);
    y_fields = fieldnames(y_temp);
    y = y_temp.(y_fields{1});

    % include averaging to estimated values
    x_temp = [];
    for j = 1:size(x,1)/20
       starti = 1 + (j-1)*20;
       endi = starti + 19;
       x_temp(j,:) = mean(x(starti:endi,:));
    end
    x = x_temp;

    % include averaging to estimate values
    y_temp = [];
    for j = 1:size(y,1)/20
      starti = 1 + (j-1)*20;
      endi = starti + 19;
      y_temp(j,:) = mean(y(starti:endi,:));
    end
    y = y_temp;
    
    % include a subset of the distances measured
    class_label = [0,1,2,3,4,5,6,7]';
    Xmat_temp = [];
    Ymat_temp = [];
    for j = 1:length(class_label)
       I = find(y == class_label(j));
       Xmat_temp = [Xmat_temp; x(I,:)];
       Ymat_temp = [Ymat_temp; y(I)];
    end
    x = Xmat_temp;
    y = Ymat_temp;

    Xmat_test_a = [];
    for j=1:size(x,2)
        Xmat_test_a(:,j) = scaleData.scaleFactor(j)*(x(:,j) + scaleData.shift(j));
    end
    X_test_a = [ones(size(Xmat_test_a,1),1), Xmat_test_a, Xmat_test_a.^2, Xmat_test_a.^3,Xmat_test_a.^4];
    Y_test_a = X_test_a*b; 
    
    Y(:,i) = Y_test_a;
end
for i=1:4
    if i==2
        hold on;
    end
    scatter(y,Y(:,i),100,'filled');
end
hold off;
legend('0 mins','~30mins','~60mins','~90mins')
xlabel('Distance from target (inches)')
ylabel('Predictions from trained regression');
title('Test prediction accuracy over time with model updates');
axis([0,7.5,0,7.5])