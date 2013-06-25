% use this script to solve for the variables E & d0 in the equation
% y = Ed + Fu where E is is constant d is an non-observable state
% representing distance. F is iteration of the system and u is the input.
%% 
E*d
%% construct 
%Fu
[A,B,C,D,E]=ssdata(sys_train);
N = 500; % how many inputs in the tx signal

F = cell(N);
for j=1:size(F,1)^2
    F{j} = 0;
end

Fadd = cell(N);
for j=1:size(Fadd,1)^2
    Fadd{j} = 0;
end
for j=1:size(Fadd,1)
    Fadd{j,j} = B;
end
Fadd = trilc(circshift(Fadd,1));
for j=1:size(Fadd,1)^2
    F{j} = F{j} + Fadd{j};
end
for i=1:(N-2)
    Fadd = trilc(circshift(Fadd,1));
    for j=1:size(Fadd,1)^2
        Fadd{j} = A*Fadd{j};
        if isequal(Fadd{j},zeros(4))
            Fadd{j} = zeros(4,1);
        end
        F{j} = F{j} + Fadd{j};
    end
end
%%
for i=1:N*N
   F{i} = C*F{i}; 
end
%%
Fsum = zeros(1500,1);
for i=1:N
    for j=1:N
        F{i,j} = F{i,j}.*tx(j);
    end
    starti = 1+3*(i-1);
    endi = starti+2;
    for j=1:N
       Fsum(starti:endi) = Fsum(starti:endi) + F{i,j};
    end
end
%%
Fu = [Fsum;Fsum;Fsum];

%%
y1 = data{43}';
y1 = reshape(y1,1500,1);
y2 = data{43}';
y2 = reshape(y2,1500,1);
y3 = data{43}';
y3 = reshape(y3,1500,1);
y = [y1;y2;y3];

%%
% Begin convex solver
m = 3;
n = 4; % number of states in the non-observable

cvx_begin quiet
    variable E0(n)
    variable E1(n)
    variable E2(n)
    variable d0(n)
    variable d1(n)
    variable d2(n)
    minimize( norm([E0'*d0;E1'*d0;E2'*d0;...
                    E0'*d1;E1'*d1;E2'*d1;...
                    E0'*d2;E1'*d2;E2'*d2],2) )
    subject to
        y = [reshape([E0'*d0*ones(1,500);E1'*d0*ones(1,500);E2'*d0*ones(1,500)],1500,1); ...
             reshape([E0'*d1*ones(1,500);E1'*d1*ones(1,500);E2'*d1*ones(1,500)],1500,1); ...
             reshape([E0'*d2*ones(1,500);E1'*d2*ones(1,500);E2'*d2*ones(1,500)],1500,1)] ...
             + Fu;
        
cvx_end
%%
% Begin convex solver
m = 3;
n = 4; % number of states in the non-observable

cvx_begin quiet
    variable E0(n)
    variable E1(n)
    variable E2(n)
    variable d0(n)
    variable d1(n)
    variable d2(n)
    minimize( norm(y - [reshape([E0'*d0*ones(1,500);E1'*d0*ones(1,500);E2'*d0*ones(1,500)],1500,1); ...
                        reshape([E0'*d1*ones(1,500);E1'*d1*ones(1,500);E2'*d1*ones(1,500)],1500,1); ...
                        reshape([E0'*d2*ones(1,500);E1'*d2*ones(1,500);E2'*d2*ones(1,500)],1500,1)] - Fu ) )
    subject to
        y = [reshape([E0'*d0*ones(1,500);E1'*d0*ones(1,500);E2'*d0*ones(1,500)],1500,1); ...
             reshape([E0'*d1*ones(1,500);E1'*d1*ones(1,500);E2'*d1*ones(1,500)],1500,1); ...
             reshape([E0'*d2*ones(1,500);E1'*d2*ones(1,500);E2'*d2*ones(1,500)],1500,1)] ...
             + Fu;
        
cvx_end