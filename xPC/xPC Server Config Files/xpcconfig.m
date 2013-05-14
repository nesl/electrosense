% default configuration
load xpcconfig.mat;
% load each xpc config property
for i=1:length(xpcconfig.actpropval)
   setxpcenv(xpcconfig.propname(i),xpcconfig.actpropval(i)); 
end
% start xpc server
xpcnetboot;