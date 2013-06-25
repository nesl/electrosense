% Implement kalman filter + linear regression 
dist = OutputLog{1};
data = OutputLog(2:end);

[A B C D K x0] = ssdata(sys_train);
A = [A ones(3,1)];
A = [A; 0 0 0 1];
B = [B; 0];
C = [C zeros(3,1)];
C = [C; 0 0 0 1];
Q = 0;
R = 0;

states = zeros(1,4);
%iterations = size(dist,1);
iterations = 100;
%%
for i=1:6
    z = data{43}(i,:)';
    z = [z;0];
    [state,K] = kalmanfilter(z,prbs(i),A,B,C,Q,R); 
    states(i,:) = state';
end