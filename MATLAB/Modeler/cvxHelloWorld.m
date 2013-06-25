m = 20; n = 10; p = 4; o = 5;
A = randn(m,n); b = randn(m,1);
C = randn(p,n); d = randn(p,1); e = rand;
cvx_begin
    variable x(o)
    minimize( norm( A * [x;x] - b, 2 ) )
    subject to
        C * [x;x] == d
        norm( x, Inf ) <= e
cvx_end