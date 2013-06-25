%% 
% 6/13/2013
% This configuration works!
% This is a steady
%sys = ss(sys_train)
Qn = 5*eye(6);
Rn = 5*eye(3);
%Nn = 0*zeros(3,3);
Nn = 0;

[A,B,C,D,K] = ssdata(sys_train);
Abar = [A, eye(3); zeros(3), eye(3)];
Bbar = [B; zeros(3,1)];
Cbar = [C, zeros(3,3)];
Dbar = D;
Kbar = [K zeros(3);zeros(3) eye(3)];
H = zeros(3,6);

Ts_out = 1e-4; % from the xPC Target Model
 sys = ss(Abar,[Bbar Kbar],Cbar,[Dbar H],Ts_out);
% msys = minreal(sys);
% [Qn Nn; Nn' Rn] Dimensions are wrong
[Kest,L,P] = kalman(sys,Qn,Rn,Nn);

% Run Kalman filter block

sys_tx = ss(A,B,C,D,Ts_out);
t = 0:Ts_out:0.100-Ts_out;
t = t';
[y,t,x] = lsim(sys_tx,trans_signal,t);



%%
index = 1;
Kresult = {};
dist_index = 39:-1:30;
for i=dist_index;
    z = [data{i}(2:991,1) data{i}(2:991,2) data{i}(3:992,3)]; % remove artificial delay due to system
    Kresult{index} = lsim(Kest, [trans_signal(1:990) z]);
    index = index + 1;
end

%% Get Linear regression parameters
% x = zeros(1,11);
% y = zeros(375,1);
% dist_2 =  dist(data_index);
% p = randperm(500);
% p_train = p(1:375);
% p_test = p(376:end);
% 
% for i=1:10
%     starti = 1+ (i-1)*375;
%     endi = starti + 374;
%     x(starti:endi,:) = out{i}(p_train,:);
%     y(starti:endi) = kron(ones(375,1),dist_2(i));
% end

x = [];
y = [];
NSamps = size(Kresult{1},1);
for i=1:10
   dstate = Kresult{i}(:,7:9);
   normstate = zeros(49,3);
   for j=1:49
       startj = 1 + 20*(j-1);
       endj = startj + 19;
       normstate(j,:) = [norm(dstate(startj:endj,1)) norm(dstate(startj:endj,2)) norm(dstate(startj:endj,3))];
   end
   % Add steady state criteria HERE
   steady_state_i = 20;
   normstate = normstate(steady_state_i:end,:);
   % Concatinate the different distances.
   x = [x; normstate];
   y = [y; kron(ones(size(normstate,1),1),dist(dist_index(i)))];
end

X = [ones(size(x,1),1),x];
[b,bint] = regress(y,X);
%% Test Linear regression
% depricated
% x_test = zeros(1,11);
% y_test = zeros(125,1);
% for i=1:10
%     starti = 1 + (i-1)*125;
%     endi = starti + 124;
%     x_test(starti:endi,:) = out{i}(p_test,:);
%     y_test(starti:endi) = kron(ones(125,1),dist_2(i));
% end
% X_test = [ones(1250,1),x_test(:,5:8)];
subplot(2,1,1);
results = X*b;
scatter(y,results)
N = size(y,1)/10;
for i=1:10
    starti = 1 + N*(i-1);
    endi = starti + (N-1);
    data_avg(i,:) = mean(results(starti:endi,:),1);
end
subplot(2,1,2);
y2 = 0:0.5:4.5;
plot(y2,data_avg)
%% (depricated)
% Using my own Kalman filter 

% 6/12/2013
% corrected alignment issue

states = cell(1);
Kgain = cell(1);

for i = 1:494
    starti = 7 + 3*(i-1);
    endi = starti + 2;
    [state K] = kalmanfilter(y1(starti:endi),tx(i),Abar,Bbar,Cbar,0,0);
    states{i} = state;
    Kgain{i} = K;
end
stability = zeros(73,8);
for i=1:73
    stability(i,:) = states{i}';
end
%%
plot(stability(:,1:4))
legend('1','2','3','4','5','6','7','8')