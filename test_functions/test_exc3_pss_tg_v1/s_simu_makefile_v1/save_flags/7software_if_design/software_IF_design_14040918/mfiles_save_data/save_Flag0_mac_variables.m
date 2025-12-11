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
function save_Flag0_mac_variables(filename, mac_ang , edprime , eqprime, psikd, psikq, vex, pmech, pelect)   % %, pss1, tg1, tg2, tg3)

    fid = fopen(filename,'w');
    if fid == -1
        error('Cannot open file.');
    end
    
    vars = { ...
        'mac_ang',  mac_ang; 
        'edprime' ,edprime;
        'eqprime',  eqprime;
        'psikd',    psikd;
        'psikq',    psikq;
        'vex',      vex;
        'pmech',    pmech;
        'pelec',    pelect;
%         'pss1',     pss1;
%         'tg1',      tg1;
%         'tg2',      tg2;
%         'tg3',      tg3;
    };

    
    for k = 1:size(vars,1)
        name = vars{k,1};
        M    = vars{k,2};

        fprintf(fid, "//%s\n", name);

        for i = 1:4        %% mac_index start at 0 in hardware ...  
            fprintf(fid, "%s[%d] = %.15f;\n", name, i-1, M(i,1));
        end

        fprintf(fid, "\n"); 
    end

    fclose(fid);
end


