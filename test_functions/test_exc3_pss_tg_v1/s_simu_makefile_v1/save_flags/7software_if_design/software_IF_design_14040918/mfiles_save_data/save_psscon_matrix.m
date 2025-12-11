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
function save_psscon_matrix(filename, matrix)
    fid = fopen(filename, 'w'); 
     [rows, cols] = size(matrix);
     scale = zeros(10,1);
    scale (1:10) =[ 2^0,2^0,2^0,2^4,2^7,2^7,2^7,2^7,2^7,2^7   ];
     for i = 1:rows
        mac_num=  pss_con(i,2);
        mac_index = mac_num -1;
        for j = 1:cols
            val = matrix(i,j);
            r_fixed = round(real(val)*scale(j));
            fprintf(fid, '%d, %d,%d,%d\n', mac_index, i-1, j, r_fixed);%% Important note : machin index begin from 0 but mac tables begin from 1 ///
        end
    end
        fprintf(fid, '//eof\n');  %����� ��?��
fprintf(fid,'%s    // pss_con: mac_index, row,col,real_fix(d)\n',filename);  %% header fil at first line cause error in verilog fscanf
   
    fclose(fid);
end
