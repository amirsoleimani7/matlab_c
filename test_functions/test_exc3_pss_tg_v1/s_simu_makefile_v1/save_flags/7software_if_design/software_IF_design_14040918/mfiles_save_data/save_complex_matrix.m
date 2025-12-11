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
function save_complex_matrix(filename, matrix, frac_bits)
    fid = fopen(filename, 'w'); 
    %fprintf(fid, 'row,col,real_fix(d),imag_fix(d)\n');
    [rows, cols] = size(matrix);
    scale = 2^frac_bits;
    for i = 1:rows
        for j = 1:cols
            val = matrix(i,j);
            r_fixed = round(real(val)*scale);
            i_fixed = round(imag(val)*scale);
            fprintf(fid, '%d,%d,%d,%d\n', i-1, j-1, r_fixed, i_fixed);
        end
    end
        fprintf(fid, 'row,col,real_fix(d),imag_fix(d)\n');
        fprintf(fid, 'eof\n');  %����� ��?��

    fclose(fid);
end



