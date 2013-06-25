function r = trilc(x)
    dim = size(x);
    if dim(1) ~= dim(2)
        r = -1;
    else
        for i=1:dim(1)
            for j=1:dim(2)
                if j-i > 0
                    x{i,j} = 0;
                end
            end
        end
        r = x;
    end
end