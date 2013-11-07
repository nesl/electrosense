for i=1:53
    rx_train_str = ['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLogOrder3\',num2str(i,'%02d'),'\rx_train_',num2str(i,'%02d')];  
    OutputLog_str = ['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLogOrder3\',num2str(i,'%02d'),'\OutputLog_',num2str(i,'%02d')];  
    % get system A matrix
    rx_train_temp = load(rx_train_str);
    fields = fieldnames(rx_train_temp);
    rx_train_temp = rx_train_temp.(fields{1});
    OutputLog_temp = load(OutputLog_str);
    fields = fieldnames(OutputLog_temp);
    OutputLog_temp = OutputLog_temp.(fields{1});
    
    [y,x,sys_train] = KalmanHelperOrder3(rx_train_temp,tx_train,OutputLog_temp,trans_signal,Ts_out);    
    
    mkdir(['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLogOrder4\',num2str(i,'%02d')]);
    save(['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLogOrder4\',num2str(i,'%02d'),'\sys_train_',num2str(i,'%02d')],'sys_train');
    save(['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLogOrder4\',num2str(i,'%02d'),'\y_',num2str(i,'%02d')],'y')
    save(['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLogOrder4\',num2str(i,'%02d'),'\x_',num2str(i,'%02d')],'x')
    OutputLog = OutputLog_temp;
    save(['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLogOrder4\',num2str(i,'%02d'),'\OutputLog_',num2str(i,'%02d')],'OutputLog')
    rx_train = rx_train_temp;
    save(['C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLogOrder4\',num2str(i,'%02d'),'\rx_train_',num2str(i,'%02d')],'rx_train')
end