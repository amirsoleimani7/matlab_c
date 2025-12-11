% s_simu.m  
% 9:59 AM 14 June 1999
% An m.file to simulate power system transients  
% using the Matlab Power System Toolbox
% This m-file takes the dynamic and load flow data and
% calculates the response of the power system to a fault
% which is specified in a switching file
% see one of the supplied data files (data2a.m) for the 
% switching file format

% version 1.8
% Author: Rui
% July 19, 2017
% add code for multiple HVDC systems 

% version 1.7
% Author: Graham Rogers
% Date September 1999
% Add smple exciter with pi avr - smppi
% version 1.6
% Author: Graham Rogers
% Date: June 1999
% Modification: add user defined hvdc control
%               modify dc so that it is integrated with a sub-multiple time constant

% version 1.5
% Author: Graham Rogers
% Date: December 1998/ January 1999
% Modification: Add svc and tcsc user defined damping controls, and add tcsc model

% version 1.4
% Author: Graham Rogers
% Date:  July 1998
% Modification: Add deltaP/omega filter

% version 1.3
% Author: Graham Rogers
% Date:  June 1998
% Modification: Add hydraulic turbine/governor

% Version: 1.2
% Author:  Graham Rogers
% Date:    August 1997
% Modification : add induction generator
% Version: 1.1
% Author:  Graham Rogers
% Date:    August 1997
% Modification : add modulation for load, exciter and governor
% Version  1.0
% Author:  Graham Rogers
% Date: February 1997
%
% (c) Copyright: Joe Chow/ Cherry Tree Scientific Software 1991 to 2020 - All rights reserved
% 
% Permission is hereby granted, free of charge, to any person obtaining a copy
% of this software and associated documentation files (the "Software"), to deal
% in the Software without restriction, including without limitation the rights
% to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
% copies of the Software, and to permit persons to whom the Software is
% furnished to do so.
% 
% The above copyright notice and this permission notice shall be included in all
% copies or substantial portions of the Software.
% 
% THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
% IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
% FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
% AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
% LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
% OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
% SOFTWARE.
%
clear all
clear global
close % close graphics windows
tic % set timer
plot_now=0;
jay = sqrt(-1);
pst_var % set up global variables 
%svc_dc=[];
% load input data from m.file
%disp('non-linear simulation')
% input data file

%[dfile,pathname]=uigetfile('d*.m','Select Data File');
%dfile='networksw.m';

%dfile='networksww.m';
%yazdian : add new config file 
dfile='config.m';
%dfile='config.m';
%dfile='config_no_pss_tg_exc.m';

%pathname='C:\Users\mo\Desktop\PST\FuncV3.2\FuncV3.2';
%if pathname == 0
%   error(' you must select a valid data file')
%else
   lfile =length(dfile);
   % strip off .m and convert to lower case
   dfile = lower(dfile(1:lfile-2));
   eval(dfile);
%end
% check for valid dynamic data file
if isempty(mac_con)
   error(' the selected file is not a valid data file')
end
if isempty(sw_con)
   error(' the selected file has no switching data')
end
%basdat = inputdlg({'Base MVA:','Base Frequency Hz:'},'Input Base Data',1,{'100','60'}); 
sys_freq = 60;
basrad = 2*pi*sys_freq; % default system frequency is 60 Hz
basmva = 100;
syn_ref = 0 ;     % synchronous reference frame
%ibus_con = []; % ignore infinite buses in transient simulation

% solve for loadflow - loadflow parameter

tol = 1e-8;   % tolerance for convergence
iter_max = 30; % maximum number of iterations
acc = 1.0;   % acceleration factor
[bus,line,line_flw] = ...
loadflow(bus,line,tol,iter_max,acc,'n',2);

%set indexes
% note: dc index set in dc load flow

%توابع دارای پسوند ایندکس نقش شماره گذاری و تعیین نوع مدل هارا دارند.
% برای مثال تابع مک ایندکس مدل و نوع ماشین ها را به همراه تعداد 
%هر یک مشخص می کند.
jjj=1;
mac_indx;
exc_indx;
tg_indx;
pss_indx;
%svc_indx(svc_dc);

% n_mac تعداد ماشین های موجود در شبکه 
%محاسبه شده در مک ایندکس

ntot = n_mac;
ngm = n_mac ;
n_pm = n_mac;
disp(' ')
disp('Performing simulation.')
%
% construct simulation switching sequence as defined in sw_con
%tswitch(1) = sw_con(1,1);
k = 1;
n_switch = length(sw_con(:,1));
k_inc = zeros(n_switch-1,1);k_incdc=k_inc;
t_switch = zeros(n_switch,1);
h=t_switch;h_dc=h;
for sw_count = 1:n_switch-1
   h(sw_count) = sw_con(sw_count,7);%specified time step
   if h(sw_count)==0, h(sw_count) = 0.01;end % default time step
   k_inc(sw_count) = fix((sw_con(sw_count+1,1)-sw_con(sw_count,1))/h(sw_count));%nearest lower integer
   h(sw_count) = (sw_con(sw_count+1,1)-sw_con(sw_count,1))/k_inc(sw_count);%step length
   t_switch(sw_count+1) =t_switch(sw_count) +  k_inc(sw_count)*h(sw_count);
   t(k:k-1+k_inc(sw_count)) = t_switch(sw_count):h(sw_count):t_switch(sw_count+1)-h(sw_count);
   k=k+k_inc(sw_count);
end

k = sum(k_inc)+1; % k is the total number of time steps in the simulation

t(k) = sw_con(n_switch,1);
[n dummy]=size(mac_con) ;
n_bus = length(bus(:,1));
%
% create zero matrices for variables to make algorithm more efficient?
v0=zeros(1,k);
v2=zeros(1,k);
z = zeros(n,k);
z1 = zeros(1,k);
zm = zeros(1,k);if n_mot>1;zm = zeros(n_mot,k);end
zig = zeros(1,k);if n_ig>1;zig = zeros(n_ig,k);end

v_p = z1;
theta = zeros(n_bus+1,k);bus_v = zeros(n_bus+1,k);
mac_ang = z; mac_spd = z; dmac_ang = z; dmac_spd = z;sin_mac_ang=z;cos_mac_ang=z;
pmech = z; pelect = z; mac_ref = z1;  sys_ref = z1; 
edprime = z; eqprime = z; dedprime = z; deqprime = z;
psikd = z; psikq = z; dpsikd = z; dpsikq = z;
pm_sig = z;
z_tg = zeros(1,k);if n_tg+n_tgh~=0;z_tg = zeros(n_tg+n_tgh,k);end
tg1 = z_tg; tg2 = z_tg; tg3 = z_tg; tg4 = z_tg; tg5 = z_tg;
dtg1 = z_tg; dtg2 = z_tg; dtg3 = z_tg;dtg4 = z_tg; dtg5 = z_tg;
tg_sig = z_tg;
z_pss = zeros(1,k);if n_pss~=0;z_pss = zeros(n_pss,k);end
pss1 = z_pss; pss2 = z_pss; pss3 = z_pss;
dpss1 = z_pss; dpss2 = z_pss; dpss3 = z_pss;
z_dpw = zeros(1,k);if n_dpw~=0; z_dpw = zeros(n_dpw,k);end
sdpw1 = z_dpw; sdpw2 = z_dpw; sdpw3 = z_dpw; sdpw4 = z_dpw; sdpw5 = z_dpw; sdpw6 = z_dpw; dpw_out = z_dpw;
dsdpw1 = z_dpw; dsdpw2 = z_dpw; dsdpw3 = z_dpw; dsdpw4 = z_dpw; dsdpw5 = z_dpw; dsdpw6 = z_dpw;
curd = z; curq = z; curdg = z; curqg = z; fldcur = z;
ed = z; eq = z; eterm = z; qelect = z;
vex = z; cur_re = z; cur_im = z; psi_re = z; psi_im = z;
ze = zeros(1,k);if n_exc~=0; ze = zeros(n_exc,k);end
V_B = ze;exc_sig = ze;
V_TR = ze; V_R = ze; V_A = ze; V_As = ze; Efd = ze; R_f = ze;
dV_TR = ze; dV_R = ze; dV_As = ze; dEfd = ze; dR_f = ze;
pss_out = ze;
vdp = zm; vqp = zm; slip = zm; 
dvdp = zm; dvqp = zm; dslip = zm;
s_mot = zm; p_mot = zm; q_mot = zm;
vdpig = zig; vqpig = zig; slig = zig; 
dvdpig = zig; dvqpig = zig; dslig = zig;
s_igen = zig; pig = zig; qig = zig; tmig = zig;

%xxx=zeros(1,1001);
%if n_svc~=0
%   B_cv = zeros(n_svc,k); dB_cv = zeros(n_svc,k);svc_sig = zeros(n_svc,k);svc_dsig=zeros(n_svc,k);
%   B_con = zeros(n_svc,k); dB_con=zeros(n_svc,k);
%   if n_dcud~=0
%      d_sig = zeros(n_dcud,k);
%      for j = 1:n_dcud
%         sv = get(svc_dc{j,1});
%         if j==1
%            xsvc_dc =zeros(sv.NumStates,k); 
%            dxsvc_dc = zeros(sv.NumStates,k);
%         else
%            xsvc_dc = [xsvc_dc;zeros(sv.NumStates,k)];
%            dxsvc_dc = [dxsvc_dc;zeros(sv.NumStates,k)];
%         end
%      end
%   else
%      xsvc_dc = zeros(1,k);
%      dxsvc_dc = zeros(1,k);
%   end
%else
%   B_cv = zeros(1,k);dB_cv = zeros(1,k); svc_sig = zeros(1,k);svc_dsig = zeros(1,k);
%   B_con = zeros(1,k);dB_con=zeros(1,k);
%   xsvc_dc = zeros(1,k);dxsvc_dc = zeros(1,k);
%   d_sig = zeros(1,k);
%end



sys_freq = ones(1,k);
disp('constructing reduced y matrices')
% step 1: construct reduced Y matrices 

disp('initializing motor,induction generator, svc and dc control models')       

%bus = svc(0,1,bus,0);%initialize svc

% this has to be done before red_ybus is used since the motor and svc 
% initialization alters the bus matrix and dc parameters are required

y_switch % calculates the reduced y matrices for the different switching conditions
disp('initializing other models')
% step 2: initialization
theta(1:n_bus,1) = bus(:,3)*pi/180;
bus_v(1:n_bus,1) = bus(:,2).*exp(jay*theta(1:n_bus,1));


flag = 0;
bus_int = bus_intprf;% pre-fault system
disp('generators')
mac_sub(0,1,bus,flag);   
mac_tra(0,1,bus,flag);
mac_em(0,1,bus,flag);
disp('generator controls')
%dpwf(0,1,bus,flag);
pss(0,1,bus,flag);
%smpexc(0,1,bus,flag);
%smppi(0,1,bus,flag);
exc_st3(0,1,bus,flag);
%exc_dc12(0,1,bus,flag);
tg(0,1,bus,flag); 
%tg_hydro(0,1,bus,flag);

% initialize svc damping controls



% initialize load modulation control


% initialize non-linear loads
if ~isempty(load_con)
   disp('non-linear loads')
   vnc = nc_load(bus,flag,Y_ncprf,Y_ncgprf);
else
   nload = 0;
end

H_sum = sum(mac_con(:,16)./mac_pot(:,1));
% step 3: perform a predictor-corrector integration 
kt = 0;
ks = 1;
k_tot = sum(k_inc);
lswitch = length(k_inc);
ktmax = k_tot-k_inc(lswitch);
bus_sim = bus;
plot_now = 0;
while (kt<=ktmax)
   k_start = kt+1;
   if kt==ktmax
      k_end = kt + k_inc(ks);
   else
      k_end = kt + k_inc(ks) + 1;
   end
   
    %yazdian:
      save_maccon_matrix('REP/Rep_mac_con.mem', mac_con);
      save_macpot_matrix('REP/Rep_mac_pot.mem', mac_pot);

   for k = k_start:k_end
      % step 3a: network solution
      % mach_ref(k) = mac_ang(syn_ref,k);
      mach_ref(k) = 0;
      pmech(:,k+1) = pmech(:,k);
      tmig(:,k+1) = tmig(:,k);
      
      if n_conv~=0;cur_ord(:,k+1) = cur_ord(:,k);end
      
      flag = 1;
      %timestep = int2str(k);
      % network-machine interface
      
      mac_sub(0,k,bus_sim,flag); 
      mac_tra(0,k,bus_sim,flag);
      mac_em(0,k,bus_sim,flag);
      % Calculate current injections and bus voltages and angles
      if k >= sum(k_inc(1:3))+1
         % fault cleared
         line_sim = line_pf2;
         bus_sim = bus_pf2;
         bus_int = bus_intpf2;
         Y1 = Y_gpf2;
         Y2 = Y_gncpf2;
         Y3 = Y_ncgpf2;
         Y4 = Y_ncpf2;
         Vr1 = V_rgpf2; 
         Vr2 = V_rncpf2;
         bo = bopf2;
          %yazdian : save fault cleared // need breakpoint avoid overwiting 
        
         
         save_complex_matrix('REP/Conf_clearF/Rep_Y_g.txt', Y1, 12);
         save_complex_matrix('REP/Conf_clearF/Rep_Y_gnc.txt', Y2, 12);
         save_complex_matrix('REP/Conf_clearF/Rep_Y_ncg.txt', Y3, 12);
         save_complex_matrix('REP/Conf_clearF/Rep_Y_nc.txt', Y4, 12);
         save_sparse_complex_matrix('REP/Conf_clearF/Rep_rec_V1.txt',Vr1, 12);
         save_sparse_complex_matrix('REP/Conf_clearF/Rep_rec_V2.txt',Vr2, 12);


         h_sol = i_simu(k,ks,k_inc,h,bus_sim,Y1,Y2,Y3,Y4,Vr1,Vr2,bo);     
      elseif k >=sum(k_inc(1:2))+1
         % near bus cleared
         line_sim = line_pf1;
         bus_sim = bus_pf1;
         bus_int = bus_intpf1;
         Y1 = Y_gpf1;
         Y2 = Y_gncpf1;
         Y3 = Y_ncgpf1;
         Y4 = Y_ncpf1;
         Vr1 = V_rgpf1; 
         Vr2 = V_rncpf1;
         bo = bopf1;
         %yazdian : save near bus cleared // need breakpoint avoid overwiting 
                 
          save_complex_matrix('REP/Conf_clearNbus/Rep_Y_g.txt', Y1, 12);
         save_complex_matrix('REP/Conf_clearNbus/Rep_Y_gnc.txt', Y2, 12);
          save_complex_matrix('REP/Conf_clearNbus/Rep_Y_ncg.txt', Y3, 12);
         save_complex_matrix('REP/Conf_clearNbus/Rep_Y_nc.txt', Y4, 12);
         save_sparse_complex_matrix('REP/Conf_clearNbus/Rep_rec_V1.txt',Vr1, 12);
         save_sparse_complex_matrix('REP/Conf_clearNbus/Rep_rec_V2.txt',Vr2, 12);
         
         
         h_sol = i_simu(k,ks,k_inc,h,bus_sim,Y1,Y2,Y3,Y4,Vr1,Vr2,bo);   
      elseif k>=k_inc(1)+1
         % fault applied
         line_sim = line_f;
         bus_sim = bus_f;
         bus_int = bus_intf;
         Y1 = Y_gf;
         Y2 = Y_gncf;
         Y3 = Y_ncgf;
         Y4 = Y_ncf;
         Vr1 = V_rgf; 
         Vr2 = V_rncf;
         bo = bof;
        %yazdian : save fault applied // need breakpoint avoid overwiting 
                 
        save_complex_matrix('REP/Conf_applyF/Rep_Y_g.txt', Y1, 12);
         save_complex_matrix('REP/Conf_applyF/Rep_Y_gnc.txt', Y2, 12);
          save_complex_matrix('REP/Conf_applyF/Rep_Y_ncg.txt', Y3, 12);
         save_complex_matrix('REP/Conf_applyF/Rep_Y_nc.txt', Y4, 12);
         save_sparse_complex_matrix('REP/Conf_applyF/Rep_rec_V1.txt',Vr1, 12);
         save_sparse_complex_matrix('REP/Conf_applyF/Rep_rec_V2.txt',Vr2, 12);
         h_sol = i_simu(k,ks,k_inc,h,bus_sim,Y1,Y2,Y3,Y4,Vr1,Vr2,bo);     
      elseif k<k_inc(1)+1
         % pre fault
         line_sim = line;
         bus_sim = bus;
         bus_int = bus_intprf;
         Y1 = Y_gprf;
         Y2 = Y_gncprf;
         Y3 = Y_ncgprf;
         Y4 = Y_ncprf;
         Vr1 = V_rgprf; 
         Vr2 = V_rncprf;
         bo = boprf;
         %yazdian : save pre fault // need breakpoint avoid overwiting 
        
         
         save_complex_matrix('REP/Conf_preFault/Rep_Y_g.txt', Y1, 12);
         save_complex_matrix('REP/Conf_preFault/Rep_Y_gnc.txt', Y2, 12);
          save_complex_matrix('REP/Conf_preFault/Rep_Y_ncg.txt', Y3, 12);
         save_complex_matrix('REP/Conf_preFault/Rep_Y_nc.txt', Y4, 12);
         save_sparse_complex_matrix('REP/Conf_preFault/Rep_rec_V1.txt',Vr1, 12);
         save_sparse_complex_matrix('REP/Conf_preFault/Rep_rec_V2.txt',Vr2, 12);

         h_sol = i_simu(k,ks,k_inc,h,bus_sim,Y1,Y2,Y3,Y4,Vr1,Vr2,bo);  
      end
      % HVDC
      exc_st3(0,k,bus_sim,flag);
      tg(0,k,bus_sim,flag);
      %pss(0,k,bus_sim,flag);
      %tg_hydro(0,k,bus_sim,flag);
      
	  % step 3b: compute dynamics and integrate
      jjj=jjj+1;
      flag = 2;
      sys_freq(k) = 1.0;
      mac_sub(0,k,bus_sim,flag); 
      mac_tra(0,k,bus_sim,flag);
      mac_em(0,k,bus_sim,flag);
      pss(0,k,bus_sim,flag);
      exc_st3(0,k,bus_sim,flag);
      tg(0,k,bus_sim,flag);
 %     if n_svc~=0
 %        v_svc = abs(bus_v(bus_int(svc_con(:,2)),k));
 %        if n_dcud~=0
 %           tot_states=0;
 %           for jj = 1:n_dcud
 %              ysvcmx = svc_dc{jj,4};ysvcmn = svc_dc{jj,5};
 %              svc_num = svc_dc{jj,2};
 %              st_state = tot_states+1; svc_states = svc_dc{jj,6}; tot_states = tot_states+svc_states; 
 %              [svc_dsig(svc_num,k),xsvc_dc(st_state:tot_states,k),dxsvc_dc(st_state:tot_states,k)] =...
 %                 svc_sud(jj,k,flag,svc_dc{jj,1},d_sig(jj,k),ysvcmx,ysvcmn,xsvc_dc(st_state:tot_states,k));
 %           end
 %        end
 %        msvc_sig(t(k),k);
 %        svc(0,k,bus_sim,flag,v_svc);
 %     end
 
      
      j = k+1;
     
      % following statements are predictor steps
      mac_ang(:,j) = mac_ang(:,k) + h_sol*dmac_ang(:,k); 
      mac_spd(:,j) = mac_spd(:,k) + h_sol*dmac_spd(:,k);
      edprime(:,j) = edprime(:,k) + h_sol*dedprime(:,k);
      eqprime(:,j) = eqprime(:,k) + h_sol*deqprime(:,k);
      psikd(:,j) = psikd(:,k) + h_sol*dpsikd(:,k);
      psikq(:,j) = psikq(:,k) + h_sol*dpsikq(:,k);
      Efd(:,j) = Efd(:,k) + h_sol*dEfd(:,k);
      V_R(:,j) = V_R(:,k) + h_sol*dV_R(:,k);
      V_As(:,j) = V_As(:,k) + h_sol*dV_As(:,k);
      R_f(:,j) = R_f(:,k) + h_sol*dR_f(:,k);
      V_TR(:,j) = V_TR(:,k) + h_sol*dV_TR(:,k);
      pss1(:,j) = pss1(:,k) + h_sol*dpss1(:,k);
      pss2(:,j) = pss2(:,k) + h_sol*dpss2(:,k);
      pss3(:,j) = pss3(:,k) + h_sol*dpss3(:,k);
      tg1(:,j) = tg1(:,k) + h_sol*dtg1(:,k);
      tg2(:,j) = tg2(:,k) + h_sol*dtg2(:,k);
      tg3(:,j) = tg3(:,k) + h_sol*dtg3(:,k);
      tg4(:,j) = tg4(:,k) + h_sol*dtg4(:,k);
      tg5(:,j) = tg5(:,k) + h_sol*dtg5(:,k);
      %B_cv(:,j) = B_cv(:,k) + h_sol*dB_cv(:,k);
      %B_con(:,j) = B_con(:,k) + h_sol*dB_con(:,k);
      %xsvc_dc(:,j) = xsvc_dc(:,k) + h_sol* dxsvc_dc(:,k);
      
	  flag = 1;
      % mach_ref(j) = mac_ang(syn_ref,j);
      mach_ref(j) = 0;
      % perform network interface calculations again with predicted states
      mac_sub(0,j,bus_sim,flag);
      mac_tra(0,j,bus_sim,flag);
      mac_em(0,j,bus_sim,flag);
      % Calculate current injections and bus voltages and angles
      if j >= sum(k_inc(1:3))+1
         % fault cleared
         bus_sim = bus_pf2;
         bus_int = bus_intpf2;
         Y1 = Y_gpf2;
         Y2 = Y_gncpf2;
         Y3 = Y_ncgpf2;
         Y4 = Y_ncpf2;
         Vr1 = V_rgpf2; 
         Vr2 = V_rncpf2;
         bo = bopf2;
         h_sol = i_simu(j,ks,k_inc,h,bus_sim,Y1,Y2,Y3,Y4,Vr1,Vr2,bo); 
        
      elseif j >=sum(k_inc(1:2))+1
         % near bus cleared
         bus_sim = bus_pf1;
         bus_int = bus_intpf1;
         Y1 = Y_gpf1;
         Y2 = Y_gncpf1;
         Y3 = Y_ncgpf1;
         Y4 = Y_ncpf1;
         Vr1 = V_rgpf1; 
         Vr2 = V_rncpf1;
         bo = bopf1;
         h_sol = i_simu(j,ks,k_inc,h,bus_sim,Y1,Y2,Y3,Y4,Vr1,Vr2,bo);   
      elseif j>=k_inc(1)+1
         % fault applied
         bus_sim = bus_f;
         bus_int = bus_intf;
         Y1 = Y_gf;
         Y2 = Y_gncf;
         Y3 = Y_ncgf;
         Y4 = Y_ncf;
         Vr1 = V_rgf; 
         Vr2 = V_rncf;
         bo = bof;
         h_sol = i_simu(j,ks,k_inc,h,bus_sim,Y1,Y2,Y3,Y4,Vr1,Vr2,bo);     
      elseif k<k_inc(1)+1  % JHC - DKF thinks k should be j
         % pre fault
         bus_sim = bus;
         bus_int = bus_intprf;
         Y1 = Y_gprf;
         Y2 = Y_gncprf;
         Y3 = Y_ncgprf;
         Y4 = Y_ncprf;
         Vr1 = V_rgprf; 
         Vr2 = V_rncprf;
         bo = boprf;
         h_sol = i_simu(j,ks,k_inc,h,bus_sim,Y1,Y2,Y3,Y4,Vr1,Vr2,bo);     
      end
      vex(:,j)=vex(:,k);
      % calculate the new value of bus angles rectifier user defined control
      pss(0,j,bus_sim,flag);
      exc_st3(0,j,bus_sim,flag);
      tg(0,j,bus_sim,flag); 
 
      
      flag = 2;
      mac_sub(0,j,bus_sim,flag);
      mac_tra(0,j,bus_sim,flag);
      mac_em(0,j,bus_sim,flag);
      pss(0,j,bus_sim,flag);
      exc_st3(0,j,bus_sim,flag);
      tg(0,j,bus_sim,flag);
%      if n_svc~=0
%         msvc_sig(t(j),j);
%         if n_dcud~=0
%            tot_states=0;
%            for jj = 1:n_dcud
%               ysvcmx = svc_dc{jj,4};ysvcmn = svc_dc{jj,5};
%               svc_num = svc_dc{jj,2};
%               st_state = tot_states+1; svc_states = svc_dc{jj,6}; tot_states = tot_states+svc_states; 
%               [svc_dsig(svc_num,j),xsvc_dc(st_state:tot_states,j),dxsvc_dc(st_state:tot_states,j)] =...
%                  svc_sud(jj,j,flag,svc_dc{jj,1},d_sig(jj,j),ysvcmx,ysvcmn,xsvc_dc(st_state:tot_states,j));
%            end
%         end
%         v_svc = abs(bus_v(bus_int(svc_con(:,2)),j));
%         bus_sim = svc(0,j,bus_sim,flag,v_svc);
%      end

      % following statements are corrector steps
      mac_ang(:,j) = mac_ang(:,k) +...
         h_sol*(dmac_ang(:,k)+dmac_ang(:,j))/2.;
      mac_spd(:,j) = mac_spd(:,k) +...
         h_sol*(dmac_spd(:,k)+dmac_spd(:,j))/2.;
      edprime(:,j) = edprime(:,k) +...
         h_sol*(dedprime(:,k)+dedprime(:,j))/2.;
      eqprime(:,j) = eqprime(:,k) +...
         h_sol*(deqprime(:,k)+deqprime(:,j))/2.;
      psikd(:,j) = psikd(:,k) +...
         h_sol*(dpsikd(:,k)+dpsikd(:,j))/2.;
      psikq(:,j) = psikq(:,k) +...
         h_sol*(dpsikq(:,k)+dpsikq(:,j))/2.;
      Efd(:,j) = Efd(:,k) +...
         h_sol*(dEfd(:,k)+dEfd(:,j))/2.;
      V_R(:,j) = V_R(:,k) +...
         h_sol*(dV_R(:,k)+dV_R(:,j))/2.;
      V_As(:,j) = V_As(:,k) +...
         h_sol*(dV_As(:,k)+dV_As(:,j))/2.;
      R_f(:,j) = R_f(:,k) +...
         h_sol*(dR_f(:,k)+dR_f(:,j))/2.;
      V_TR(:,j) = V_TR(:,k) +...
         h_sol*(dV_TR(:,k)+dV_TR(:,j))/2.;
		 
      pss1(:,j) = pss1(:,k) +h_sol*(dpss1(:,k)+dpss1(:,j))/2.;
      pss2(:,j) = pss2(:,k) +h_sol*(dpss2(:,k)+dpss2(:,j))/2.;
      pss3(:,j) = pss3(:,k) +h_sol*(dpss3(:,k)+dpss3(:,j))/2.;
      tg1(:,j) = tg1(:,k) + h_sol*(dtg1(:,k) + dtg1(:,j))/2.;
      tg2(:,j) = tg2(:,k) + h_sol*(dtg2(:,k) + dtg2(:,j))/2.;
      tg3(:,j) = tg3(:,k) + h_sol*(dtg3(:,k) + dtg3(:,j))/2.;
      tg4(:,j) = tg4(:,k) + h_sol*(dtg4(:,k) + dtg4(:,j))/2.;
      tg5(:,j) = tg5(:,k) + h_sol*(dtg5(:,k) + dtg5(:,j))/2.;
      %B_cv(:,j) = B_cv(:,k) + h_sol*(dB_cv(:,j) + dB_cv(:,k))/2.;
      %B_con(:,j) = B_con(:,k) + h_sol*(dB_con(:,j) + dB_con(:,k))/2.;
      %xsvc_dc(:,j) = xsvc_dc(:,k) + h_sol*(dxsvc_dc(:,j) + dxsvc_dc(:,k))/2.;
      end
   kt = kt + k_inc(ks);
   ks = ks+1; 
end
V1 = bus_v(bus_int(line(:,1)),:);
V2 = bus_v(bus_int(line(:,2)),:);
R = line(:,3); X = line(:,4); B = line(:,5);
tap = line(:,6); phi = line(:,7);
[ilf,ilt]=line_cur(V1,V2,R,X,B,tap,phi);%line currents
et = toc;
ets = num2str(et);
disp(['elapsed time = ' ets 's'])
%flag=0;
flag = 1;
while(flag == 0)
   disp('You can examine the system response')
   disp('Type 1 to see all machine angles in 3D')
   disp('     2 to see all machine speed deviation in 3D')
   disp('     3 to see all machine turbine powers')
   disp('     4 to see all machine electrical powers')
   disp('     5 to see all field voltages')
   disp('     6 to see all bus voltage magnitude in 3D')
   disp('     7 to see the line power flows')
   disp('     0 to quit and plot your own curves')
   sel = 0;
   if sel == 1
      mesh(t,[1:1:n_mac],mac_ang*180/pi)
      title('machine angles')
      xlabel('time in seconds')
      ylabel('internal generator number')
      zlabel('angle in degrees')
      disp('paused: press any key to continue')
      pause
   elseif sel == 2
      lt = length(t);
      mesh(t,[1:1:n_mac],mac_spd- ones(n_mac,lt))
      title('machine speed deviations')
      xlabel('time in seconds')
      ylabel('internal generator number')
      zlabel('speed in pu')
      disp('paused: press any key to continue')
      pause
   elseif sel == 3
      plot(t,pmech)
      title('turbine power')
      xlabel('time in seconds')
      ylabel('power in pu on generator base')
      disp('paused: press any key to continue')
      pause
   elseif sel == 4
      plot(t,pelect)
      title('generator electrical power')
      xlabel('time in seconds')
      ylabel('power in pu on system base')
      disp('paused: press any key to continue')
      pause
   elseif sel == 5
      plot(t,Efd)
      title('Generator field voltages')
      xlabel('time in seconds')
      ylabel('voltage in pu')
      disp('paused: press any key to continue')
      pause
   elseif sel == 6
      [nbus,dum] = size(bus_v);
      mesh(t,(1:1:nbus),abs(bus_v))
      xlabel('time in seconds')
      ylabel('bus number')
      zlabel('voltage in pu')
      disp('paused: press any key to continue')
      pause
   elseif sel == 7
      nline = length(line(:,1));
      if nline<50
         [S1,S2] = line_pq(V1,V2,R,X,B,tap,phi);
         plot(t,real(S1));
         xlabel('time in seconds')
         ylabel(' power flow per unit')
         disp('paused: press any key to continue')
         pause
      else
         % ask for lines to be plotted
         line_range = input(' enter a rangle of lines less than 50, ie 1:49   >');
         if isempty(line_range);line_range = 1:49;end
         V1 = bus_v(bus_int(line(line_range,1)),:);
         V2 = bus_v(bus_int(line(line_range,2)),:);
         R = line(line_range,3); X = line(line_range,4); 
         B = line(line_range,5);
         tap = line(line_range,6); phi = line(line_range,7);
         [S1,S2] = line_pq(V1,V2,R,X,B,tap,phi);
         plot(t,real(S1));
         xlabel('time in seconds')
         ylabel(' power flow per unit')
         disp('paused: press any key to continue')
         pause
      end
   elseif sel == 0
      flag = 1;
   else
      error('invalid selection')
   end
end

% tidy workspace
% clear B H_sum IHT  R  SHT   VLT          
% clear V_rgf V_rgpf1 V_rgpf2 V_rgprf V_rncf V_rncpf1 V_rncpf2 V_rncprf Vdc_ref      
% clear Vr1 Vr2 X Y1 Y2 Y3 Y4           
% clear Y_gf Y_gncf Y_gncpf1 Y_gncpf2 Y_gncprf Y_gpf1       
% clear Y_gpf2 Y_gprf Y_ncf Y_ncgf Y_ncgpf1 Y_ncgpf2 Y_ncgprf Y_ncpf1 Y_ncpf2 Y_ncprf      
% clear ac_bus ac_line ans b_num1 b_num2  bo bof bopf1 bopf2 boprf                  
% clear bus_ang bus_f bus_idx bus_int bus_intf bus_intpf1 bus_intpf2 bus_intprf   
% clear bus_pf1 bus_pf2 bus_sim  cap_idx conv_num  dc2_idx dc_TA  dc_TA_idx    
% clear dc_TB dc_TB_idx dc_TE dc_TE_idx dc_TF dc_TF_idx dc_TR dc_TR_idx    
% clear dc_idx dc_noTB_idx dc_noTE_idx dc_noTR_idx dc_pot dcc_con      
% clear dcc_pot dci_dc dciud_idx dcl_con  dcli_idx dcr_dc dcr_states dcrud_idx    
% clear dcsp_con dcud_idx dfile dpw_Td_idx dpw_con dpw_idx dpw_mb_idx   
% %clear dpw_pot dpw_pss_idx dtcscud_idx  dummy et ets exc_con exc_pot      
% clear dpw_pot dpw_pss_idx dtcscud_idx  dummy et ets 
%       % JHC 1/19/2017 keep exc_pot for Vref and exc_con for K_E     
% clear f f_nearbus f_type flag h h_sol i i_aci i_acr i_dcinj      
% clear i_idx i_plot ibus_con idig idmot igbus igen_con igen_int igen_pot ind_con      
% clear ind_int ind_pot inv_ac_bus inv_ac_line inv_par iqig iqmot        
% clear j jay jj k k_end k_inc k_start k_tot ks kt           
% clear ktmax l_cap l_no_cap lfile line_f line_flw line_par line_pf1 line_pf2 line_sim     
% clear lmod_con lmod_idx lmod_pot lmon_con  load_con load_pot lswitch lt mac_con mac_em_idx   
% clear mac_ib_em mac_ib_idx mac_ib_sub mac_ib_tra mac_int  mac_pot mac_sub_idx mac_tra_idx  
% clear mld_con motbus n n_bus n_conv n_dc n_dc2 n_dcl n_dcud n_dpw n_em n_exc n_ib n_ib_em      
% clear n_ib_sub n_ib_tra n_ig n_lmod n_mac n_mot n_pm n_pss n_rlmod n_smp n_st3 n_sub n_svc        
% clear n_switch n_tcsc n_tcscud n_tg n_tgh n_tra nbus         
% clear ndci_ud ndcr_ud netg_con ngm nload no_cap_idx no_ind_idx not_ib_idx   
% clear ntot pathname  phi pig plot_now psidpp psiqpp pss_T pss_T2 pss_T4  pss_T4_idx pss_con      
% clear pss_exc_idx pss_idx pss_mb_idx pss_noT4_idx pss_p_idx pss_pot pss_sp_idx r_idx        
% clear rec_ac_bus rec_ac_line rec_num rec_par ric_idx rlmod_con rlmod_idx rlmod_pot rpc_idx scr_con sel          
% clear smp_TA smp_TA_idx smp_TB smp_TB_idx smp_TR smp_TR_idx smp_idx smp_noTA_idx smp_noTB_idx 
% clear smp_no_TR_idx st3_TA st3_TA_idx st3_TB st3_TB_idx st3_TR st3_TR_idx st3_idx st3_noTA_idx 
% clear st3_noTB_idx st3_noTR_idx st_state stab_con sv svc_con svc_dc       
% clear svc_idx svc_pot svcll_idx sw_con sw_count syn_ref t_init t_switch tap          
% clear tapi tapr tcsc_con tcsc_dc tcsct_idx  tcsvf_idx tg_con tg_idx tg_pot       
% clear tg_sig tgh_idx timestep tload tmax tmaxi tmaxr tmin tmini tminr        
% clear tot_states tstep tstepi tstepr tswitch vdig vdmot vnc vqig vqmot ydcrmn ydcrmx  
% clear z z1 z_dpw z_pss z_tg zdc zdcl ze zig zm 
%// save config for hardware configuration 
%yazdian add these functions :
function save_complex_matrix(filename, matrix, frac_bits)
    fid = fopen(filename, 'w'); 
    fprintf(fid, 'row,col,real_fix(d),imag_fix(d)\n');
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
        fprintf(fid, 'eof\n');  %����� ��?��

    fclose(fid);
end
%yazdian add these functions :
% === ��?�� ����?� sparse ����� ===
function save_sparse_complex_matrix(filename, matrix, frac_bits)
    [i, j, v] = find(matrix);  % ��� �������? �?� ���

    fid = fopen(filename, 'w');
     fprintf(fid, 'sparce matrix :row,col,real_fix(d),imag_fix(d)\n');

    scale = 2^frac_bits;
    for k = 1:length(v)
        r_fixed = round(real(v(k)) * scale);
        i_fixed = round(imag(v(k)) * scale);
        fprintf(fid, '%d,%d,%d,%d\n', i(k)-1, j(k)-1, r_fixed, i_fixed);
    end
        fprintf(fid, 'eof\n');  % ����� ��?��

    fclose(fid);
end
