%% Test SVM Model
%% Get Data
%%
X = {};
Y = {};
tx_train = tx_train(1:5000,:);
for i = 1:4
    sys_train_str = ['sys_train_',num2str(i,'%02d')];
    x_str = ['x_',num2str(i,'%02d')];
    y_str = ['y_',num2str(i,'%02d')];
    output_str = ['OutputLog_',num2str(i,'%02d')];
    rx_train_str = ['rx_train_',num2str(i,'%02d')];
    
    out_temp =load(output_str);
    out_fields = fieldnames(out_temp);
    OutputLog_temp = out_temp.(out_fields{1});
    rx_train_temp =load(rx_train_str);
    rx_train_fields = fieldnames(rx_train_temp);
    rx_train_temp = rx_train_temp.(rx_train_fields{1});
    
    % get SID A matrix
    %A_temp = load(sys_train_str);
    %A_fields = fieldnames(A_temp);
    %sys_train = A_temp.(A_fields{1});
    
    [y,x,sys_train] = KalmanHelperOrder3(rx_train_temp,tx_train,OutputLog_temp,trans_signal,Ts_out)
    
    % get singular and/or norm values
    Snorm(i) = norm(sys_train);
    
    % must load trans_signal & Ts_out before hand
    %X_temp = load(x_str);
    %X_fields = fieldnames(X_temp);    
    %x = X_temp.(X_fields{1});
    %Y_temp = load(y_str);
    %Y_fields = fieldnames(Y_temp);
    %y = Y_temp.(Y_fields{1});
    
    % include averaging to estimated values
    xtemp2 = [];
    for j = 1:size(x,1)/20
       starti = 1 + (j-1)*20;
       endi = starti + 19;
       xtemp2(j,:) = mean(x(starti:endi,:));
    end
    x = [xtemp2, kron(ones(size(xtemp2,1),1),Snorm(i))];

    % include averaging to estimate values
    ytemp2 = [];
    for j = 1:size(y,1)/20
      starti = 1 + (j-1)*20;
      endi = starti + 19;
      ytemp2(j,:) = mean(y(starti:endi,:));
    end
    y = ytemp2;
    
    % include a subset of the distances measured
    class_label = 0:1:7;
    Xmat_temp = [];
    Ymat_temp = [];
    for j = 1:length(class_label)
       I = find(y == class_label(j));
       Xmat_temp = [Xmat_temp; x(I,:)];
       Ymat_temp = [Ymat_temp; y(I)];
    end
    
    X{i} = Xmat_temp;
    Y{i} = Ymat_temp;
end

%% SVM 1vAll -> binary
%%
Y_test_out = [];
for h=1:4
    % load tests
    Ymat_test = Y{h};
    Xmat_test = X{h};
    
    clear results;
    for i = 1:length(Ymat_test)
        for j = 1:length(class_label)
            r = svmclassify(svmTestStruct(j), Xmat_test(i,:),'showplot',true);
            results(i,j) = r;
        end
    end
    results = [Ymat_test, results];
    results_old = results;
    
    fuzzy_classify = zeros(2,1);
    % SVM Drill Down
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
                    svmStruct_subset = svmtrain(Xmat_train_subset, Ymat_train_subset,'kernel_function','rbf','method','QP');

                    Xmat_test_subset = Xmat_test(i,[k,4]);
                    index = index + 1;
                    r_subset(index) = svmclassify(svmStruct_subset,Xmat_test_subset);
                end
                %weight_snr = [0.2;0.2;0.6];
                naive_avg(j-1) = mean(r_subset);
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
    Y_test_out(:,h) = fuzzy_classify;
end
%%
for i=1:4
    if i==2
        hold on;
    end
    scatter(Y{1},Y_test_out(:,i),100,'filled');
end
hold off;
legend('0 mins','~30mins','~60mins','~90mins')
xlabel('Distance from target (inches)')
ylabel('Predictions from trained regression');
title('Test prediction accuracy over time with model updates');
axis([0,7.5,0,7.5])