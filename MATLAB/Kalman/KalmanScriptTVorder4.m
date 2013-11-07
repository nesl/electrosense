%%
% 6/20/2013
% Time varying Kalman filter

% 6/25/2013
% Added polynomial regressions and sum square error calculations
%%
load OutputLog
load trans_signal
load sys_train
load Ts_out
%%
dist = OutputLog{1};
data = OutputLog(:,2:end);
data_length = size(OutputLog,2) - 1;
%%
% Initialization variables
[A,B,C,D,K] = ssdata(sys_train);
Abar = [A, eye(4); zeros(4), eye(4)];
Bbar = [B; zeros(4,1)];
Cbar = [C, zeros(3,4)];
Dbar = D;
Kbar = [K zeros(4);zeros(4,3) eye(4)];
H = zeros(4,8);
%Qn = eye(6);
Qn = 1;
Rn = eye(3);
Nn = 0;
u = trans_signal;
Nsamps = 980;
t = 0:Ts_out:Nsamps*Ts_out-Ts_out;
t = t';

index = 1;
Kresult = {};
dist_index = 39:-1:1;
ye = {};
errcov = {};

% Kalman Filter
for i=dist_index
    % artificial delay in the sampling hardware taken out;
    %yv = [data{i}(2:981,1) data{i}(2:981,2) data{i}(2:981,3)]; % remove artificial delay due to system
    yv = data{i};
    yv_mean = mean(yv,1);
    yv = yv - kron(ones(size(yv,1),1),yv_mean); % model does not incorporate mean

    P = Bbar*Qn*Bbar';         % Initial error covariance
    P(5,5) = 1; P(6,6)=1; P(7,7)=1; P(8,8)=1; % VERY IMPORANT
    x = zeros(8,1);           % Initial condition on the state
    xv = zeros(length(t),length(x));

    for j=1:length(t)
      % Measurement update
      Mn = P*Cbar'/(Cbar*P*Cbar'+ Rn);
      x = x + Mn*(yv(j,:)'-Cbar*x);  % x[n|n]
      P = (eye(8)-Mn*Cbar)*P;     % P[n|n]

      ye{index,j} = Cbar*x;
      errcov{index,j} = Cbar*P*Cbar';

      % Time update
      x = Abar*x + Bbar.*u(j);        % x[n+1|n]
      P = Abar*P*Abar' + Bbar*Qn*Bbar';     % P[n+1|n]

      % get state x
      xv(j,:) = x';
    end
    
    Kresult{index,1} = xv;
    index = index + 1;
end

% prepare for Regression
x = [];
x_separate = {};
y = [];
NSamps = size(Kresult{1},1);
for i=1:size(Kresult,1);
   dstate = Kresult{i}(:,5:8);
   Nsig = floor(size(Kresult{1},1)/20);
   normstate = zeros(Nsig,4);
   for j=1:Nsig
       startj = 1 + 20*(j-1);
       endj = startj + 19;
       normstate(j,:) = [norm(dstate(startj:endj,1)) norm(dstate(startj:endj,2)) norm(dstate(startj:endj,3)) norm(dstate(startj:endj,4))];
   end
   % Add steady state criteria HERE
   % simply delay the samples accepted
   %steady_state_i = 20;
   steady_state_i = 30;
   normstate = normstate(steady_state_i:end,:);
   
   %
   %normstate = mean(normstate)
   
   % Concatinate the different distances.
   %x_separate{i-1} = normstate;
   x = [x; normstate];
   y = [y; kron(ones(size(normstate,1),1),dist(dist_index(i)))];
end

%% Linear

X = [ones(size(x,1),1) x ];
[b,bint] = regress(y,X);
results = X*b;
%errlin = sse(y-results);
scatter(y,results);
xlabel('distance from target')
ylabel('results');
%% Quadratic

Xquad = [ones(size(x,1),1) x x.^2];
[bquad,bintquad,r,rint,stats] = regress(y,Xquad);
resultsquad = Xquad*bquad;
%errquad = sse(y-resultsquad);
scatter(y,resultsquad);
xlabel('distance from target')
ylabel('results');
%% Cube

Xcube = [ones(size(x,1),1) x x.^2 x.^3];
[bcube bintcube] = regress(y,Xcube);
resultscube = Xcube*bcube;
% errcube = sse(y-resultscube);
scatter(y,resultscube);
xlabel('distance from target')
ylabel('results');
%% 4th

X4th = [ones(size(x,1),1) x x.^2 x.^3 x.^4];
[b4th bint4th,r,rint,stats] = regress(y,X4th);
results4th = X4th*b4th;
%err4th = sse(y-results4th);
scatter(y,results4th);
xlabel('distance from target')
ylabel('results');
%%
errtrend = [errlin errquad errcube err4th];
scatter(1:4,errtrend)
xlabel('Regression Order')
ylabel('Sum Square Error')

%%
% save data
x_06 = x;
y_06 = y;
sys_train_06 = sys_train;
OutputLog_06 = OutputLog;
rx_train_06 = rx_train;
rx_train_sqr_06 = rx_train_sqr; 
rx_train_b_06 = rx_train_b;
bintquad_06 = bintquad;
bquad_06 = bquad;
bint4th_06 = bint4th;
b4th_06 = b4th;
save('x_06','x_06');
save('y_06','y_06');
save('sys_train_06','sys_train_06');
save('OutputLog_06','OutputLog_06');
save('rx_train_06','rx_train_06');
save('rx_train_sqr_06','rx_train_sqr_06');
save('rx_train_b_06','rx_train_b_06');
save('bint4th_06','bint4th_06');
save('b4th_06','b4th_06');
save('bintquad_06','bintquad_06')
save('bquad_06','bquad_06')
%% used for showing varations over time in environment
sys_train_04 = sys_train;
rx_train_04 = rx_train;
rx_train_b_04 = rx_train_b;
x_04 = x;
y_04 = y;
OutputLog_04 = OutputLog;
save('rx_train_b_04','rx_train_b_04');
save('rx_train_04','rx_train_04');
save('sys_train_04','sys_train_04');
save('x_04','x_04');
save('y_04','y_04');
save('OutputLog_04','OutputLog_04');

%% TEst

xtemp2 = [];
for j = 1:size(x,1)/20
   starti = 1 + (j-1)*20;
   endi = starti + 19;
   xtemp2(j,:) = mean(x(starti:endi,:));
end

% include averaging to estimate values
ytemp2 = [];
for j = 1:size(y,1)/20
  starti = 1 + (j-1)*20;
  endi = starti + 19;
  ytemp2(j,:) = mean(y(starti:endi,:));
end
%%
scatter(ytemp2(1:2:16),xtemp2(1:2:16,1));
hold on;
scatter(ytemp2(1:2:16),xtemp2(1:2:16,2));
scatter(ytemp2(1:2:16),xtemp2(1:2:16,3));
scatter(ytemp2(1:2:16),xtemp2(1:2:16,4));
hold off;
legend('1','2','3','4')
