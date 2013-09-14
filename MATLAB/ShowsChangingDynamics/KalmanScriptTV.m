%%
% 6/20/2013
% Time varying Kalman filter

% 6/25/2013
% Added polynomial regressions and sum square error calculations
%%
load OutputLog
load trans_signal
load sys_train
load Ts_out;
%%
dist = OutputLog4{1};
data = OutputLog4(:,2:end);
data_length = size(OutputLog4,2) - 1;
%%
% Initialization variables
[A,B,C,D,K] = ssdata(sys_train);
Abar = [A, eye(3); zeros(3), eye(3)];
Bbar = [B; zeros(3,1)]';
Cbar = [C, zeros(3,3)];
Dbar = D;
Kbar = [K zeros(3);zeros(3) eye(3)];
H = zeros(3,6);
Qn = eye(6);
Rn = eye(3);
Nn = 0;
u = trans_signal;
Nsamps = 990;
t = 0:Ts_out:Nsamps*Ts_out-Ts_out;
t = t';

index = 1;
Kresult = {};
dist_index = 39:-1:20;
ye = {};
errcov = {};

% Kalman Filter
for i=dist_index
    % artificial delay in the sampling hardware taken out;
    yv = [data{i}(2:991,1) data{i}(2:991,2) data{i}(3:992,3)]; % remove artificial delay due to system
    yv_mean = mean(yv);
    yv = yv - kron(ones(size(yv,1),1),yv_mean); % model does not incorporate mean
    
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
% Regression section (Build)

x = [];
x_separate = {};
y = [];
NSamps = size(Kresult{1},1);
for i=1:size(Kresult,1);
   dstate = Kresult{i}(:,4:6);
   Nsig = floor(size(Kresult{1},1)/20);
   normstate = zeros(Nsig,3);
   for j=1:Nsig
       startj = 1 + 20*(j-1);
       endj = startj + 19;
       normstate(j,:) = [norm(dstate(startj:endj,1)) norm(dstate(startj:endj,2)) norm(dstate(startj:endj,3))];
   end
   % Add steady state criteria HERE
   % simply delay the samples accepted
   steady_state_i = 20;
   normstate = normstate(steady_state_i:end,:);
   % Concatinate the different distances.
   %x_separate{i-1} = normstate;
   x = [x; normstate];
   y = [y; kron(ones(size(normstate,1),1),dist(dist_index(i)))];
end

%% Linear

X = [ones(size(x,1),1) x];
[b,bint] = regress(y,X);
results = X*b;
errlin = sse(y-results);
%% Quadratic

Xquad = [ones(size(x,1),1) x x.^2];
[bquad,bintquad] = regress(y,Xquad);
resultsquad = Xquad*bquad;
errquad = sse(y-resultsquad);

%% Cube

Xcube = [ones(size(x,1),1) x x.^2 x.^3];
[bcube bintcube] = regress(y,Xcube);
resultscube = Xcube*bcube;
errcube = sse(y-resultscube);

%% 4th

X4th = [ones(size(x,1),1) x x.^2 x.^3 x.^4 ];
[b4th bint4th] = regress(y,X4th);
results4th = X4th*b4th;
err4th = sse(y-results4th);
scatter(y,results4th);
xlabel('distance from target')
ylabel('results');
%%
errtrend = [errlin errquad errcube err4th];
scatter(1:4,errtrend)
xlabel('Regression Order')
ylabel('Sum Square Error')