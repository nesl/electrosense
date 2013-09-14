x1 = x;
%%
x2 = x;
%%
x3 = x;
%%
cmp = [x1(:,3) x2(:,3)];
subplot(2,1,1); scatter(1:size(cmp,1),cmp(:,1)); 
subplot(2,1,2); scatter(1:size(cmp,1),cmp(:,2));

%%
set = 20;
Nsets = size(x,1)/set;
randi = randperm(Nsets);
%%
trainsubset = randi(1:Nsets/2)';
testsubset = randi(Nsets/2+1:end)';
trainset = [];
testset = [];
for i=2:11
    trainset = [trainset; trainsubset + (Nsets)*(i-1)];
    testset = [testset; testsubset + (Nsets)*(i-1)];
end
ytrain = y(trainset,:);
ytest = y(testset);
x1train = x1(trainset,:);
x1test = x1(testset,:);
x2train = x2(trainset,:);
x2test = x2(testset,:);
x3train = x3(trainset,:);
x3test = x3(testset,:);
% 2 fold cross validation
ytrain = [ytrain; ytrain; ytrain];
ytest = [ytest; ytest; ytest];
xtest = [x1test;x2test;x3test];
xtest = [xtest,xtest.^2,xtest.^3,xtest.^4];
xtrain = [x1train;x2train;x3train];
xtrain = [xtrain,xtrain.^2,xtrain.^3,xtrain.^4];

% Adjust folding below here
k = 0:.01:0.1;
B1 = ridge(ytrain, xtrain, k);
plot(k, B1');
xlabel('Ridge parameter'); ylabel('Standardized coef.');

m = mean(xtrain);
s = std(xtrain,0,1)';
B0 = [];
for i=1:size(B1,2)
    temp = B1(:,i)./s;
    B0(:,i) = [mean(ytrain)-m*temp; temp];
end

%% test the regularization results
xtesting = [ones(size(xtest,1),1),xtest];
disthat = xtesting*B0;
ytesting = kron(ones(1,size(disthat,2)),ytest);
diff = ytesting - disthat;
err = [];
for i=1:size(disthat,2)
   err(i) = sse(diff(:,i));
end
plot(k, err);
err
% plot regression estimates
scatter(ytest, disthat(:,1))

%% Testing with new data
xtesting = [ones(size(x(31:330,:),1),1),x(31:330,:),x(31:330,:).^2,x(31:330,:).^3,x(31:330,:).^4];
disthat = xtesting*B0(:,1);
ytesting = y(31:330);
diff = ytesting - disthat;
err = sse(diff);
scatter(y(31:330), disthat(:,1))
