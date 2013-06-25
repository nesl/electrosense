function [state,K] = kalmanfilter(z,signal,Ainput,Binput,Hinput,Qinput,Rinput)
%
%
persistent A B H Q R
persistent x P
persistent firstRun

if isempty(firstRun)
    A = Ainput;
    B = Binput;
    H = Hinput;
    Q = Qinput;
    R = Rinput;
    
    %x = zeros(size(Ainput,1),1);
    x = zeros(8,1);
    P = 20*eye(size(Ainput,1));
    
    firstRun = 1;
end

xp = A*x + B*signal;
Pp = A*P*A' + Q;
K = Pp*H'*inv(H*Pp*H' + R);

x = xp + K*(z - H*xp);

state = x;

P = Pp - K*H*Pp;
