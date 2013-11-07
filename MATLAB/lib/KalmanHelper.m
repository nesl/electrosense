function [Y,X] = KalmanHelper(OutputLog, sys_train, trans_signal, Ts_out)
%
% helper script for one time use
%
    dist = OutputLog{1};
    data = OutputLog(:,2:end);
    data_length = size(OutputLog,2) - 1;

    % Initialization variables
    [A,B,C,D,K] = ssdata(sys_train);
    Abar = [A, eye(3); zeros(3), eye(3)];
    Bbar = [B; zeros(3,1)];
    Cbar = [C, zeros(3,3)];
    Dbar = D;
    Kbar = [K zeros(3);zeros(3) eye(3)];
    H = zeros(3,6);
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
        yv = [data{i}(2:981,1) data{i}(2:981,2) data{i}(2:981,3)]; % remove artificial delay due to system
        yv_mean = mean(yv);
        yv = yv - kron(ones(size(yv,1),1),yv_mean); % model does not incorporate mean

        P = Bbar*Qn*Bbar';         % Initial error covariance
        P(4,4) = 1; P(5,5)=1; P(6,6)=1;
        x = zeros(6,1);           % Initial condition on the state
        xv = zeros(length(t),length(x));

        for j=1:length(t)
          % Measurement update
          Mn = P*Cbar'/(Cbar*P*Cbar'+ Rn);
          x = x + Mn*(yv(j,:)'-Cbar*x);  % x[n|n]
          P = (eye(6)-Mn*Cbar)*P;     % P[n|n]

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

       %
       %normstate = mean(normstate)

       % Concatinate the different distances.
       %x_separate{i-1} = normstate;
       x = [x; normstate];
       y = [y; kron(ones(size(normstate,1),1),dist(dist_index(i)))];
    end

    Y=y;
    X=x;
end
