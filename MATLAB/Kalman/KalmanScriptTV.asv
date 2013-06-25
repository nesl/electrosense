%%
% 6/20/2013
% Time varying Kalman filter
%%
load OutputLog
load trans_signal
load sys_train
load Ts_out;
%%
dist = OutputLog{1};
data = OutputLog(:,2:end);
data_length = size(OutputLog,2) - 1;
%%
% Initialization variables
[A,B,C,D,K] = ssdata(sys_train);
Abar = [A, eye(3); zeros(3), eye(3)];
Bbar = [B; zeros(3,1)]';
Cbar = [C, zeros(3,3)];
Dbar = D;
Kbar = [K zeros(3);zeros(3) eye(3)];
H = zeros(3,6);

Rn = eye(3);
Nn = 0;
u = trans_signal;
Nsamps = 990;
t = 0:Ts_out:Nsamps*Ts_out-Ts_out;
t = t';

index = 1;
Kresult = {};
dist_index = 39:-1:30;
ye = {};
errcov = {};
for i=dist_index;
    yv = [data{i}(2:991,1) data{i}(2:991,2) data{i}(3:992,3)]; % remove artificial delay due to system
    yv_mean = mean(yv);
    yv = yv - kron(ones(size(yv,1),1),yv_mean);
    P = Bbar*Qn*Bbar';         % Initial error covariance
    x = zeros(6,1);           % Initial condition on the state
    xv = zeros(length(t),length(x));

    for j=1:length(t)
      % Measurement update
      Mn = P*Cbar'/(Cbar*P*Cbar'+ Rn);
      x = x + Mn*(yv(j)-Cbar*x);  % x[n|n]
      P = (eye(6)-Mn*Cbar)*P;     % P[n|n]

      ye{index,j} = Cbar*x;
      errcov{index,j} = Cbar*P*Cbar';

      % Time update
      x = Abar*x + Bbar'*u(j);        % x[n+1|n]
      P = Abar*P*Abar' + Bbar*Qn*Bbar';     % P[n+1|n]

      % get state x
      xv(j,:) = x';
    end
    
    Kresult{index,1} = xv;
    index = index + 1;
end
%% Regression section (Build)

x = [];
x_separate = {};
y = [];
NSamps = size(Kresult{1},1);
for i=1:10
   dstate = Kresult{i}(:,4:6);
   normstate = zeros(49,3);
   for j=1:49
       startj = 1 + 20*(j-1);
       endj = startj + 19;
       normstate(j,:) = [norm(dstate(startj:endj,1)) norm(dstate(startj:endj,2)) norm(dstate(startj:endj,3))];
   end
   % Add steady state criteria HERE
   steady_state_i = 1;
   normstate = normstate(steady_state_i:end,:);
   % Concatinate the different distances.
   %x_separate{i-1} = normstate;
   x = [x; normstate];
   y = [y; kron(ones(size(normstate,1),1),dist(dist_index(i)))];
end

%% Linear

X = [x ones(size(x,1),1)];
[b,bint] = regress(y,X);
results = X*b;
errlin = sse(y-results);
%% Quadratic

Xquad = [x.^2 x ones(size(x,1),1)];
[bquad,bintquad] = regress(y,Xquad);
resultsquad = Xquad*bquad;
errquad = sse(y-resultsquad);

%% Cube

Xcube = [x.^3 x.^2 x ones(size(x,1),1)];
[bcube bintcube] = regress(y,Xcube);
resultscube = Xcube*bcube;
errcube = sse(y-resultscube);

%% 4th

X4th = [x.^4 x.^3 x.^2 x ones(size(x,1),1)];
[b4th bint4th] = regress(y,X4th);
results4th = X4th*b4th;
err4th = sse(y-results4th);
scatter(y,results4th);
%%
errtrend = [errlin errquad errcube err4th];
scatter(1:4,errtrend)
xlabel('order')