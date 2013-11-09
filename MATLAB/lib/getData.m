function [sys_train,OutputLog,x,y,rx_train] = getData(basePath, sets)
    %[sys_train,OutputLog,x,y] = getData(basePath, sets)
    %pc example
    %'C:\Users\newton\AeroFS\NESL_Software\electrosense\DATA\ModelWeekLogOrder4\AL\'
    %mac example 
    %'/Users/newton/AeroFS/NESL_Software/electrosense/DATA/ModelWeekLogOrder4/AL/'
    
    sys_train = -1;
    OutputLog = -1;
    x = -1;
    y = -1;
    if ispc
    sys_train_str = [basePath,num2str(sets,'%02d'),'\sys_train_',num2str(sets,'%02d'),'.mat'];
    bquad_str = [basePath,num2str(sets,'%02d'),'\bquad_',num2str(sets,'%02d'),'.mat'];
    b4th_str = [basePath,num2str(sets,'%02d'),'\b4th_',num2str(sets,'%02d'),'.mat'];
    x_str = [basePath,num2str(sets,'%02d'),'\x_',num2str(sets,'%02d'),'.mat'];
    y_str = [basePath,num2str(sets,'%02d'),'\y_',num2str(sets,'%02d'),'.mat'];
    outputlog_str = [basePath,num2str(sets,'%02d'),'\OutputLog_',num2str(sets,'%02d'),'.mat'];
    rx_train_str = [basePath,num2str(sets,'%02d'),'\rx_train_',num2str(sets,'%02d'),'.mat'];
    else
    sys_train_str = [basePath,num2str(sets,'%02d'),'/sys_train_',num2str(sets,'%02d'),'.mat'];
    bquad_str = [basePath,num2str(sets,'%02d'),'/bquad_',num2str(sets,'%02d'),'.mat'];
    b4th_str = [basePath,num2str(sets,'%02d'),'/b4th_',num2str(sets,'%02d'),'.mat'];
    x_str = [basePath,num2str(sets,'%02d'),'/x_',num2str(sets,'%02d'),'.mat'];
    y_str = [basePath,num2str(sets,'%02d'),'/y_',num2str(sets,'%02d'),'.mat'];
    outputlog_str = [basePath,num2str(sets,'%02d'),'/OutputLog_',num2str(sets,'%02d'),'.mat'];
    rx_train_str = [basePath,num2str(sets,'%02d'),'/rx_train_',num2str(sets,'%02d'),'.mat'];
    end

    if exist(sys_train_str)
        temp = load(sys_train_str);
        tempFields = fieldnames(temp);
        sys_train = temp.(tempFields{1});
    end
    
    if exist(outputlog_str)
        temp = load(outputlog_str);
        tempFields = fieldnames(temp);
        OutputLog = temp.(tempFields{1});
    end
    
    if exist(x_str)
        temp = load(x_str);
        tempFields = fieldnames(temp);        
        x = temp.(tempFields{1});
    end

    if exist(y_str)
        temp = load(y_str);
        tempFields = fieldnames(temp);
        y = temp.(tempFields{1});
    end
    
    if exist(rx_train_str)
        temp = load(rx_train_str);
        tempFields = fieldnames(temp);
        rx_train = temp.(tempFields{1});
    end
end