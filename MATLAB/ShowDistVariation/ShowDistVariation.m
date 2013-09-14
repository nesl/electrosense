dist = OutputLog{1};
data = OutputLog(2:40);

probe1 = [];
probe3 = [];
probe7 = [];
probe5 = [];
mean1 = [];
mean3 = [];
mean7 = [];
mean5 = [];

Dsamp = 39;
Nsamp = 980;
Psamp = 20;

for i=1:size(data,2)
    probe1(:,i) =  data{i}(2:981,1);
    mean1(i) = mean(probe1(:,i));
    probe1(:,i) = probe1(:,i) - kron(ones(size(probe1(:,i),1),1),mean1(i));
    
    probe3(:,i) = data{i}(2:981,4);
    mean3(i) = mean(probe3(:,i));
    probe3(:,i) = probe3(:,i) - kron(ones(size(probe3(:,i),1),1),mean3(i));
    
    probe7(:,i) = data{i}(2:981,6);
    mean7(i) = mean(probe7(:,i));
    probe7(:,i) = probe7(:,i) - kron(ones(size(probe7(:,i),1),1),mean7(i));
    
    probe5(:,i) = data{i}(2:981,5);
    mean5(i) = mean(probe5(:,i));
    probe5(:,i) = probe5(:,i) - kron(ones(size(probe5(:,i),1),1),mean5(i));
end
for i=1:size(probe1,2)
    mean1Vpp(i) = sum(abs(probe1(:,i)))/Nsamp*2;
    mean3Vpp(i) = sum(abs(probe3(:,i)))/Nsamp*2;
    mean5Vpp(i) = sum(abs(probe5(:,i)))/Nsamp*2;
    mean7Vpp(i) = sum(abs(probe7(:,i)))/Nsamp*2;
end
probe1Trough = zeros(Dsamp,1);
probe3Trough = zeros(Dsamp,1);
probe5Trough = zeros(Dsamp,1);
probe7Trough = zeros(Dsamp,1);
for i=1:Dsamp
    for j=1:Nsamp/20
        startj = 1 + Psamp*(j-1);
        endj = startj + 9;
        probe1Trough(i) = probe1Trough(i) + sum(probe1(startj:endj,i));
        probe3Trough(i) = probe3Trough(i) + sum(probe3(startj:endj,i));
        probe5Trough(i) = probe5Trough(i) + sum(probe5(startj:endj,i));
        probe7Trough(i) = probe7Trough(i) + sum(probe7(startj:endj,i));
    end
end
probe1Trough = probe1Trough./Nsamp*2;
probe3Trough = probe3Trough./Nsamp*2;
probe5Trough = probe5Trough./Nsamp*2;
probe7Trough = probe7Trough./Nsamp*2;
probe1Peak = zeros(Dsamp,1);
probe3Peak = zeros(Dsamp,1);
probe5Peak = zeros(Dsamp,1);
probe7Peak = zeros(Dsamp,1);
for i=1:size(probe1,2)
    for j=1:Nsamp/20
        startj = 1 + Psamp*(j-1) + 10;
        endj = startj + 9;
        probe1Peak(i) = probe1Peak(i) + sum(probe1(startj:endj,i));
        probe3Peak(i) = probe3Peak(i) + sum(probe3(startj:endj,i));
        probe5Peak(i) = probe5Peak(i) + sum(probe5(startj:endj,i));
        probe7Peak(i) = probe7Peak(i) + sum(probe7(startj:endj,i));
    end
end
probe1Peak = probe1Peak./Nsamp*2;
probe3Peak = probe3Peak./Nsamp*2;
probe5Peak = probe5Peak./Nsamp*2;
probe7Peak = probe7Peak./Nsamp*2;
%%
plot(dist,[probe1Peak,probe3Peak,probe5Peak,probe7Peak])
xlabel('dist')
ylabel('mean peak')
legend('p1,','p3','p5','p7')
%%
plot(dist,[probe1Trough,probe3Trough,probe5Trough,probe7Trough])
xlabel('dist')
ylabel('mean trough')
legend('p1,','p3','p5','p7')
%%
plot(dist,[mean1Vpp',mean3Vpp',mean5Vpp',mean7Vpp']);
xlabel('dist')
ylabel('mean Vpp')
legend('p1,','p3','p5','p7')
%%
plot(dist,[mean1', mean3', mean5', mean7']);
xlabel('dist')
ylabel('mean')
legend('p1','p3','p5','p7')

