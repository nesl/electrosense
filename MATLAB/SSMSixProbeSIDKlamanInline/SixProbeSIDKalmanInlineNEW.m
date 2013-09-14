% This script runs SID and Kalman filter in series creating an online
% system identification. The model is calculated using the opposite facing
% sensors that are unaffected targets.

% Old regression values in MATLAB\ShowsChangingDynamics/B1 uses 4th order
% and bias 
load B1
%% Build Model
dist = OutputLog{1};
data = OutputLog(:,2:end);
%%
dist_index = 10:-1:10;
yhat_all = {};
ytrue_all = {};
index = 1;
for i = dist_index
    % freq = 500 Hz
    Ts_out = 1e-4; % Ts_out is the received sampling frequency
    Nsamp = 990;
    Nsamp_window = 990;

    % Split the front and back sensors
    % Use the back sensors (4,5,6) for modeling
    % Use the front sensors (1,2,3) for target detection
    rx_train_front = data{i}(2:Nsamp+1,1:3); % there is an unknown zero value for the first element
    rx_train_back = data{i}(2:Nsamp+1,4:6);
    tx = trans_signal;

    % take out any DC bias
    rx_average_train_front = mean(rx_train_front,1);
    rx_train_front = rx_train_front - kron(ones(size(rx_train_front,1),1),rx_average_train_front);
    rx_average_train_back = mean(rx_train_back,1);
    rx_train_back = rx_train_back - kron(ones(size(rx_train_back,1),1),rx_average_train_back);

    % loop for sliding window
    yhat = [];
    ytrue = [];
%    for l=0:(Nsamp-Nsamp_window)
    for l=0
        data_back = iddata(rx_train_back(1+l:Nsamp_window+l,:),tx(1+l:Nsamp_window+l),Ts_out);
        data_front = iddata(rx_train_front(1+l:Nsamp_window+l,:),tx(1+l:Nsamp_window+l),Ts_out);
        % get state-space model using subspace method
        [sys_train, x0_train_back] = n4sid(data_front,'best'); % 'best' extimates the order
        % Kalman Initialization variables
    end
end
%%        
        for q=1
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

        %t = 0:Ts_out:Nsamps*Ts_out-Ts_out;
        %t = t';

        %index = 1;
        %ye = {};
        %errcov = {};

        P = Bbar*Qn*Bbar';        % Initial error covariance
        x = zeros(6,1);           % Initial condition on the state
        xv = zeros(Nsamp_window,length(x));

        yv_window = rx_train_front(1+l:Nsamp_window+l,:);
        end

        % Kalman Loop
        for j=1:Nsamp_window
            % Measurement update
            Mn = P*Cbar'/(Cbar*P*Cbar'+ Rn);
            x = x + Mn*(yv_window(j,:)' - Cbar*x);  % x[n|n]
            P = (eye(6)-Mn*Cbar)*P;     % P[n|n]

            % not used
            %ye{index,j} = Cbar*x;
            %errcov{index,j} = Cbar*P*Cbar';

            % Time update
            x = Abar*x + Bbar'*trans_signal(j);        % x[n+1|n]
            P = Abar*P*Abar' + Bbar*Qn*Bbar';     % P[n+1|n]

            % get state x
            xv(j,:) = x';
        end

        Kresult = xv;
        
        % Regression section (Build)
        x = []; y = [];
        % find norm over single cycle
        dstate = Kresult(:,4:6);
        SampPerCyc = 20;
        Nsig = floor(size(Kresult,1)/SampPerCyc);
        normstate = zeros(Nsig,3);
        for j=1:Nsig
           startj = 1 + SampPerCyc*(j-1);
           endj = startj + SampPerCyc - 1;
           normstate(j,:) = [norm(dstate(startj:endj,1)) norm(dstate(startj:endj,2)) norm(dstate(startj:endj,3))];
        end
        
        % Add steady state criteria HERE
        % simply delay the samples accepted
        steady_state_i = 20;
        normstate = normstate(steady_state_i:end,:);
        % Concatinate the different distances.
        x = [x; normstate];
        y = [y; kron(ones(size(normstate,1),1),dist(i))];

        % regression
        xtrain = [ones(size(x,1),1), x, x.^2, x.^3, x.^4];
        yhat = [yhat; xtrain*B1];
        ytrue = [ytrue; y];
    end
    
    yhat_all{index} = yhat;
    ytrue_all{index} = ytrue;
    index = index + 1;
end
