function [Y,X,sys_train] = KalmanHelperOrder4(rx_train, tx_train, OutputLog, trans_signal, Ts_out)
%
% helper script for one time use
%
    data_train = iddata(rx_train, tx_train, Ts_out); 
    % get state-space model using subspace method
    [sys_train, x0_train] = n4sid(data_train,4); % 'best' extimates the order
    
    dist = OutputLog{1};
    data = OutputLog(:,2:end);
    data_length = size(OutputLog,2) - 1;

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

    Y=y;
    X=x;
end
