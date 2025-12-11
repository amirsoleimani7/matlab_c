%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Company: IUT
% Engineer: M.Yazdian
% 
% Create Date: 1404/09
% Design Name: PST  software modeling
% Module Name: s_sim
% Project Name: power system toolbox
% Target Devices: 
% Description: 	save matlab variables in file prepared for ARM in Fpga		
% Dependencies: 	
% 
% Revision:
% Revision 0.01 -  1404/09/18 : File Created
% Additional Comments:
% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function save_sparse_complex_matrix(filename, matrix, frac_bits)
    [i, j, v] = find(matrix);  % ��� �������? �?� ���

    fid = fopen(filename, 'w');
    % fprintf(fid, 'sparce matrix :row,col,real_fix(d),imag_fix(d)\n');

    scale = 2^frac_bits;
    for k = 1:length(v)
        r_fixed = round(real(v(k)) * scale);
        i_fixed = round(imag(v(k)) * scale);
        fprintf(fid, '%d,%d,%d,%d\n', i(k)-1, j(k)-1, r_fixed, i_fixed);
    end
         fprintf(fid, '//sparce matrix :row,col,real_fix(d),imag_fix(d)\n');
        fprintf(fid, 'eof\n');  % ����� ��?��

    fclose(fid);
end
