function cvx_expert_check( fname, varargin )

global cvx___
if cvx___.expert, return; end
if ~isempty( varargin ) && ~any(cellfun('isclass',varargin,'cvx')), return; end
fprintf( 1, [ 'CVX Warning:\n', ...
    '   Models involving "%s" or other functions in the log, exp, and entropy\n', ...
    '   family are solved using an experimental successive approximation method.\n', ...
    '   The method requires multiple calls to the solver, so it can be slow; and\n', ...
    '   in certain cases it fails to converge. See Appendix D of the the user''s\n', ...
    '   guide for more information about this method, and for instructions on how\n', ...
    '   to suppress this warning in the future.\n' ], fname );
    cvx___.expert = true;
    % Note that we do *not* call cvx_save_prefs here. We only save the
    % preferences if an explicit setting of "cvx_expert true" is made.
end