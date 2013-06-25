load error_norm
load dist
error_mean = mean(error_norm,2);
error_std = std(error_norm,0,2);
subplot(2,1,1);
for i=1:size(error_norm,2)
    error_std_pt(:,i) = error_norm(:,i) - error_mean;
end

dist_exp = kron(ones(5,1),dist');
plot(dist_exp',error_std_pt');
legend('10 V','8 V','6 V','4 V','2 V');
xlabel('Distance from left tank wall (inches)');
ylabel('Error above the mean (DC removed)');
title('Al target edge at 3.25"');
grid on;
