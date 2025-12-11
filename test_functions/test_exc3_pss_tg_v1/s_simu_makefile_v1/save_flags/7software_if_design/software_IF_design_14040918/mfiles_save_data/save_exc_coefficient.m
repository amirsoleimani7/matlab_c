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
function fid = save_exc_coefficient(filename , exc_con,exc_pot)


%  FROM SOFTWARE   : mac_num , exc_vep_coefficient_mag , exc_vep_coefficient_phase       exc_ve_coefficient_mag ,exc_ve_coefficient_phase,
%     

%      //exc_vep_coefficient  = (exc_pot_1 + j*exc_pot_2) ;
%                   exc_vep_coefficient_mag[i] =     
%                   exc_vep_coefficient_phase[i] =

%   exc_ve_coefficient = jay*(exc_con(i,15)+ (exc_pot(i,1)+jay*exc_pot(i,2))*exc_con(i,16))     
%               exc_ve_coefficient_mag[i] =    ;     mag,//fxs_23_14
%               exc_ve_coefficient_phase[i] =    ;   phase,//fxs_20_16 like mac_ang
%---------------------------------% write in file ----------------------------------------------
% file format :
% machine_id   pot_mag   pot_phase   coef_mag   coef_phase   ve_mag   ve_phase
%--------------------------------------------------------------------------------

N = size(exc_pot,1);
fid = fopen(filename,'w');

fprintf(fid, "%% machine_id  exc_vep_coef_mag  exc_vep_coef_phase  exc_ve_coef_mag  exc_ve_coef_phase  \n");
 mag_scale = 2^7;
 phase_scale = 2^12;
 mag_scale_ve = 2^16;
 phase_scale_ve = 2^12;
for i = 1:N

    machine_id = exc_con(i,2);   % ����� ���?�

    %% ----- exc_pot complex -----
    exc_vep_coefficient = exc_pot(i,1) + 1j*exc_pot(i,2);
    exc_vep_coef_mag   = abs(exc_vep_coefficient);
    exc_vep_coef_phase = angle(exc_vep_coefficient);   % rad
    exc_vep_coef_mag_fix = round(exc_vep_coef_mag * mag_scale);
    exc_vep_coef_phase_fix = round(exc_vep_coef_phase * phase_scale);



    %% ----- coef = exc_con15 + exc_con16 * pot -----
    tmp_ve_coef = exc_con(i,15) + exc_con(i,16) * exc_vep_coefficient;
    
    %% ----- exc_ve = j * coef -----
    exc_ve_coef = 1j * tmp_ve_coef;
    exc_ve_coef_mag   = abs(exc_ve_coef);
    exc_ve_coef_phase = angle(exc_ve_coef);

    exc_ve_coef_mag_fix = round(exc_ve_coef_mag * mag_scale_ve);
    exc_ve_coef_phase_fix = round(exc_ve_coef_phase * phase_scale_ve);%fxs24_12


    %% ---- Write ONE LINE ----
    fprintf(fid, "%d  %d  %d  %d  %d  %d  %d\n", ...
        machine_id, ...
        exc_vep_coef_mag_fix, exc_vep_coef_phase_fix, ...
        exc_ve_coef_mag_fix, exc_ve_coef_phase_fix );%fxs24_16 , fi(mag,1,24_16)  , fi(phase,16_12)
end

fclose(fid);
end




