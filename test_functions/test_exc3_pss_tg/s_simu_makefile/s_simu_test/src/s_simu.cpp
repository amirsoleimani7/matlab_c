#include "../include/H_header.h"

using namespace std;
using namespace Eigen;

void s_simu(MatrixXd& bus,MatrixXd& line,MatrixXd& mac_con,MatrixXd& load_con,MatrixXd& exc_con,
             MatrixXd& pss_con , MatrixXd& tg_con ,MatrixXd& sw_con)
{
    complex<double> jay(0.0, 1.0); // sqrt(-1)
    
    double sys_freq = 50;
    double basrad = sys_freq * 2 * M_PI;
    double basmva = 100.0;
    double syn_ref = 0.0;
    double tol = 1e-8;
    double iter_max = 30;
    double acc = 1.0;
    double flag = 2; // flag does not change the functionality of the load_flow (why?)
    string display = "n";

    MatrixXd bus_sol_1,line_sol_1,line_flow_1; // the bus_sol_1 sould e the same as bus
    load_flow(bus,line,tol,iter_max,acc,display,flag ,bus_sol_1 , line_sol_1 , line_flow_1);    

    bus = bus_sol_1;
    //result of the load_flow
    cout << "bus_sol_1 is : \n" << bus_sol_1 << "\n";
    cout << "line_sol_1 is : \n" << line_sol_1 << "\n";
    cout << "line_flow_1 is : \n" << line_flow_1 << "\n";
    

    // set indexes 
    // note : dc index set in dc load flow


    // init matrixes for the mac_indx 
    MatrixXd mac_pot , mac_em_idx , mac_tra_idx , mac_sub_idx , mac_int , not_ib_idx;
    int macmax, n_tot , n_ig , n_em , n_tra, n_sub ;
    int n_mac = 0  ,ngm = 0;

    mac_indx(mac_con , mac_pot , mac_em_idx , mac_tra_idx , mac_sub_idx , mac_int
            ,macmax , n_mac , n_tot , n_ig, n_em , n_tra ,n_sub , not_ib_idx ,ngm);

    //mac_indx result 
    cout << "mac_con after mac_index is : \n" << mac_con << "\n";
    cout << "mac_em_idx is :\n" << mac_em_idx <<"\n";
    cout << "mac_tra_idx is : \n" << mac_tra_idx <<"\n";
    cout << "mac_sub_idx is  : \n" << mac_sub_idx <<"\n";
    cout << "mac_int is : \n " << mac_int <<"\n";
    cout << "not_ib_idx is :\n" << not_ib_idx << "\n";
    cout << "macmax is : " << macmax << "\n";
    cout << "n_mac is : " << n_mac <<"\n";
    cout << "n_tot is : " << n_tot << "\n";
    cout << "n_ig is : " << n_ig << "\n";
    cout << "n_em is : " << n_em <<"\n";
    cout << "n_tra is : " << n_tra <<"\n";
    cout << "n_sub is : " << n_sub <<"\n";
    cout << "ngm is : " << ngm << "\n";
    
    //init matrixes for exc_indx
    MatrixXd st3_idx , st3_TA , st3_TA_idx , st3_noTA_idx;
    MatrixXd exc_pot , st3_TB , st3_TB_idx , st3_noTB_idx , st3_TR , st3_TR_idx ,st3_noTR_idx;
    int n_exc , n_st3;

    exc_indx(exc_con , exc_pot , n_exc , st3_idx , n_st3 , st3_TA , st3_TA_idx ,st3_noTA_idx
            ,st3_TB , st3_TB_idx , st3_noTB_idx , st3_TR , st3_TR_idx , st3_noTR_idx);


    //exc_indx result
    cout << "exc_indx : -------------\n";

    cout << "n_st3  is : " << n_st3 << "\n";
    cout << "n_exc : " << n_exc << "\n";

    cout << "exc_con : \n" << exc_con << "\n";
    cout << "exc_pot : \n" << exc_pot << "\n";
    cout << "n_exc : \n" << n_exc << "\n";
    cout << "st3_idx : \n" << st3_idx << "\n";
    cout << "n_st3 : \n" << n_st3 << "\n";

    cout << "st3_TA : \n" << st3_TA << "\n";
    cout << "st3_TA_idx : \n" << st3_TA_idx << "\n";
    cout << "st3_noTA_idx : \n" << st3_noTA_idx << "\n";

    cout << "st3_TB : \n" << st3_TB << "\n";
    cout << "st3_TB_idx : \n" << st3_TB_idx << "\n";
    cout << "st3_noTB_idx : \n" << st3_noTB_idx << "\n";


    cout << "st3_TR : \n" << st3_TR << "\n";
    cout << "st3_TR_idx : \n" << st3_TR_idx << "\n";
    cout << "st3_noTR_idx : \n" << st3_noTR_idx << "\n";

    cout << "-------------\n";
    
    //init matrixes for tg_indx
    MatrixXd tg_idx , tgh_idx;
    int n_tg, n_tgh ;
    Tg_idx(tg_con , tg_idx , n_tg , tgh_idx , n_tgh);

    //tg_indx result 
    cout << "-------tg_indx-----\n";
    cout << "n_tg is : " << n_tg << "\n"; 
    cout << "n_tgh is : " << n_tgh << "\n";
    cout << "tg_idx is : \n" << tg_idx << "\n";
    cout << "tgh_idx is : \n" << tgh_idx <<  "\n";    
    cout << "------------\n";


    //init matrixes for pss_indx    

    MatrixXd pss_pot; 
    MatrixXd pss_idx, pss_sp_idx, pss_p_idx, pss_mb_idx ,pss_exc_idx;
    MatrixXd pss_T, pss_T2 ,pss_T4 ,pss_T4_idx , pss_noT4_idx ,pss_noT4;

    int n_pss;
    
    pss_indx(pss_con , mac_con, exc_con,pss_idx , n_pss , pss_sp_idx , pss_p_idx , pss_mb_idx , pss_exc_idx , 
            pss_T , pss_T2 , pss_T4 , pss_T4_idx , pss_noT4);

    
    //pss_indx result 
    cout << "pss_idx ------------------------\n";
    cout << "pss_idx is : \n "<< pss_idx <<"\n";   
    cout << "pss_mb_idx is : \n" << pss_mb_idx <<"\n";
    cout << "pss_con is : \n" << pss_con <<"\n";

    cout << "pss_exc_idx is" << pss_exc_idx.rows() << " " << pss_exc_idx.cols() << "\n";
    cout << "pss_exc_idx is : \n" << pss_exc_idx <<"\n";

    cout << "exc_con is : \n" << exc_con  <<"\n ";
    cout << "pss_exc_idx is : \n" << pss_exc_idx << "\n";
    cout << "pss_T is : \n" << pss_T << "\n";
    cout << "pss_T2 is : \n" << pss_T2 << "\n";
    cout << "pss_T4 is : \n" << pss_T4 << "\n";
    cout << "pss_T4_idx is : \n" << pss_T4_idx << "\n";
    cout << "pss_noT4 is : \n" << pss_noT4 << "\n";
    cout << "pss_sp_idx is : \n" << pss_sp_idx << "\n"; 
    cout << "pss_p_idx is : \n" << pss_p_idx << "\n";
    cout << "n_pss : " << n_pss << "\n";
    cout << "------------------------\n";

    int ntot = n_mac;
    ngm = n_mac;
    int n_pm = n_mac;       

    int k = 1; // this is zero based and should be 0 instead of 1(to work in my functions)

    int n_switch = sw_con.col(0).rows(); // how many rows are there in the sw_con ... 

    MatrixXd k_inc = MatrixXd::Zero(n_switch -1 ,1);
    MatrixXd t_switch = MatrixXd::Zero(n_switch, 1);
    MatrixXd h = t_switch;

    MatrixXd t(0 ,1); // change the size dynamicly 

    for (int li = 0; li < n_switch -1 ; ++li) { // not sure about this loop at all 
        h(li, 0) = sw_con(li, 6);

        if (h(li, 0) == 0) {
            h(li, 0) = 0.01; 
        }   

        k_inc(li, 0) = std::floor((sw_con(li + 1, 0) - sw_con(li, 0)) / h(li, 0));


        h(li, 0) = (sw_con(li + 1, 0) - sw_con(li, 0)) / k_inc(li, 0);

        t_switch(li + 1, 0) = t_switch(li, 0) + k_inc(li, 0) * h(li, 0);

        for (int lj = 0; lj < k_inc(li, 0); ++lj) {
            t.conservativeResize(t.rows() +1  , NoChange);
            t(t.rows() -1  , 0) = t_switch(li, 0) + lj * h(li, 0);
        }

        k += k_inc(li, 0);
    }

  

    t.conservativeResize(t.rows() +1  , NoChange);
    t(k -1 , 0) = sw_con(n_switch -1 ,  0);

    // int n_bus = bus.col(0).rows();
    // int n = mac_con.col(0).rows();

    // MatrixXd z(n , k);
    // MatrixXd z1(1 , k);

    // MatrixXd mac_ang = z , mac_spd = z , dmac_ang = z , dmac_spd = z , pmech = z;
    // MatrixXd pelect = z  , edprime = z , eqprime  = z , dedprime = z , deqprime = z;
    // MatrixXd psikd = z  , psikq = z , dpsikq = z , pm_sig = z , curd = z , curq = z;
    // MatrixXd durdg = z , curqg = z , fldcur = z , ed = z , eq = z , eterm = z , qelect = z;
    // MatrixXd vex = z, cur_re = z ,  cur_im = z , psi_re = z , psi_im = z;

    // MatrixXd v_p = z1 , mac_ref = z1 , sys_ref = z1;

    // MatrixXd theta(n_bus + 1, k);
    // MatrixXd bus_v(n_bus + 1, k);

    // MatrixXd z_tg(1 , k);

    // MatrixXd tg1 = z_tg , tg2 = z_tg , tg3 = z_tg , tg4 = z_tg , tg5 = z_tg;
    // MatrixXd dtg1 = z_tg , dtg2 = z_tg , dtg3 = z_tg , dtg4 = z_tg , dtg5 = z_tg;
    // MatrixXd tg_sig = z_tg;

    // if(n_tg != 0){
    //     MatrixXd z_tg(n_tg , k);
    // }


    // if(n_pss == 0){
    //     MatrixXd z_pss(1 , k);
    //     MatrixXd pss1 = z_pss , pss2 = z_pss , pss3 = z_pss;
    //     MatrixXd dpss1 = z_pss , dpss2 = z_pss , dpss3 = z_pss;
    // }else{
    //     MatrixXd z_pss(n_pss , k);
    //     MatrixXd pss1 = z_pss , pss2 = z_pss , pss3 = z_pss;
    //     MatrixXd dpss1 = z_pss , dpss2 = z_pss , dpss3 = z_pss;
    // }



    // if(n_exc == 0){
    //     MatrixXd ze(1 , k);
    //     MatrixXd V_B = ze , V_TR = ze , V_R = ze , V_A = ze , V_As = ze;
    //     MatrixXd Efd = ze , R_f = ze , dv_TR = ze , dV_R = ze , dV_As = ze;
    //     MatrixXd dEfd = ze , dR = ze , dR_f = ze , pss_out = ze;
    // }else{
    //     MatrixXd ze(n_pss , k);
    //     MatrixXd V_B = ze , V_TR = ze , V_R = ze , V_A = ze , V_As = ze;
    //     MatrixXd Efd = ze , R_f = ze , dv_TR = ze , dV_R = ze , dV_As = ze;
    //     MatrixXd dEfd = ze , dR = ze , dR_f = ze , pss_out = ze;
    // }

    // MatrixXd m_sys_freq(1 , k); // matrix of system frequency .. 

    // y_switch(bus , line, load_con , mac_con , sw_con);
    
    // ------------------------------------------------------------------------------------------------
    flag = 0;   
    int i = 0;
    MatrixXd bus_int = bus.col(0);

    MatrixXd cur_re, cur_im, psidpp, psikd, psikq, psiqpp, psi_re, psi_im;
    MatrixXd mac_ang, mac_spd, eqprime, edprime;
    MatrixXd curd, curq, curdg, curqg, fld_cur;
    MatrixXd vex, eterm, theta, ed, eq;
    MatrixXd pmech, pelect, qelect;
    MatrixXd dmac_ang, dmac_spd, deqprime, dedprime;
    MatrixXd mcurmag;
    MatrixXd busnum, phi, eqra, E_Isat, edra;
    MatrixXcd curr, V, ei, rot;    

    cout << "n_sub is :\n" << n_sub << "\n";
    mac_sub(i , flag , bus_sol_1 , mac_con , bus_int , mac_sub_idx , n_sub , basmva , mac_pot , cur_re , cur_im , 
            psidpp , psikd , psikq , psiqpp , psi_re , psi_im ,mac_ang , mac_spd , eqprime , edprime , curd ,
        curq , curdg , curqg , fld_cur , vex , eterm , theta  , ed , eq , pmech , pelect , qelect , dmac_ang ,
    dmac_spd , deqprime , dedprime , mcurmag , busnum , phi , eqra , E_Isat, edra , curr,V , ei , rot);

    cout << "----------results for mac_sub-----\b";  
    cout << "theta is:\n" << theta << "\n";
    cout << "curd is:\n" << curd << "\n";
    cout << "curdg is:\n" << curdg << "\n";
    cout << "curq is:\n" << curq << "\n";
    cout << "curqg is:\n" << curqg << "\n";
    cout << "ed is:\n" << ed << "\n";
    cout << "edprime is:\n" << edprime << "\n";
    cout << "eq is:\n" << eq << "\n";
    cout << "eqprime is:\n" << eqprime << "\n";
    cout << "eterm is:\n" << eterm << "\n";
    cout << "mac_ang is:\n" << mac_ang << "\n";
    cout << "mac_spd is:\n" << mac_spd << "\n";
    cout << "pelect is:\n" << pelect << "\n";
    cout << "qelect is:\n" << qelect << "\n";
    cout << "pmech is:\n" << pmech << "\n";
    cout << "phi is:\n" << phi << "\n";
    cout << "psi_im is:\n" << psi_im << "\n";
    cout << "psi_re is:\n" << psi_re << "\n";
    cout << "vex is:\n" << vex << "\n";
    cout << "rot (real) is:\n" << rot.real() << "\n";
    cout << "rot (imag) is:\n" << rot.imag() << "\n";
    cout << "curr (real) is:\n" << curr.real() << "\n";
    cout << "curr (imag) is:\n" << curr.imag() << "\n";
    cout << "ei (real) is:\n" << ei.real() << "\n";
    cout << "ei (imag) is:\n" << ei.imag() << "\n";
    cout << "eqra is:\n" << eqra << "\n";
    cout << "psidpp is:\n" << psidpp << "\n";
    cout << "psikd is:\n" << psikd << "\n";
    cout << "edra is:\n" << edra << "\n";
    cout << "psiqpp is:\n" << psiqpp << "\n";
    cout << "psikq is:\n" << psikq << "\n";
    cout << "V (real) is:\n" << V.real() << "\n";
    cout << "V (imag) is:\n" << V.imag() << "\n";
    cout << "E_Isat is:\n" << E_Isat << "\n";
    cout << "fld_cur is:\n" << fld_cur << "\n";

    
    
    
    // create placeholder for mac_tra 
    // MatrixXd mac_pot;
    // MatrixXd cur_re, cur_im, psidpp, psikd, psikq, psiqpp, psi_re, psi_im;
    // MatrixXd mac_ang, mac_spd, eqprime, edprime;
    // MatrixXd curd, curq, curdg, curqg, fld_cur;
    // MatrixXd vex, eterm, theta, ed, eq; 
    // MatrixXd pmech, pelect, qelect;
    // MatrixXd dmac_ang, dmac_spd, deqprime, dedprime;
    // MatrixXd mcurmag;
    // MatrixXd busnum, phi, eqra, E_Isat, edra;
    // MatrixXcd curr, V, ei, rot, eprime;
    
    MatrixXcd eprime(4 ,1); // not sure about the sizes  ... 

    cout << "n_tra is : " << n_tra << "\n";
    mac_tra(bus ,  mac_con , bus_int , mac_tra_idx , i , k , flag  ,n_tra , basmva , mac_pot , cur_re
            , cur_im , psidpp , psikd , psikq , psiqpp , psi_re , psi_im , mac_ang,  mac_spd, eqprime , edprime, 
            curd, curq , curdg , curqg , fld_cur , vex , eterm , theta , ed , eq , pmech , pelect , qelect , dmac_ang , 
            dmac_spd , deqprime , dedprime , mcurmag  ,busnum , phi , eqra , E_Isat , edra , curr,  V , ei , rot , eprime);
                    
    cout << "result in mac_Tra is :----- \n";
    cout << "theta is \n" << theta << "\n";
    cout << "curd is \n" << curd << "\n";
    cout << "curdg is \n" << curdg << "\n";
    cout << "curq is \n" << curq << "\n";
    cout << "curqg is \n" << curqg << "\n";
    cout << "ed is \n" << ed << "\n";
    cout << "edprime is \n" << edprime << "\n";
    cout << "eq is \n" << eq << "\n";
    cout << "eqprime is \n" << eqprime << "\n";
    cout << "etern  is \n" << eterm << "\n";
    cout << "mac_ang  is \n" << mac_ang << "\n";
    cout << "mac_spd  is \n" << mac_spd << "\n";
    cout << "pelect  is \n" << pelect << "\n";
    cout << "qelect  is \n" << qelect << "\n";
    cout << "pmech  is \n" << pmech << "\n";
    cout << "phi  is \n" << phi << "\n";
    cout << "psi_im  is \n" << psi_im << "\n";
    cout << "psi_re  is \n" << psi_re << "\n";
    cout << "vex  is \n" << vex << "\n";
    cout << "rot_re   is \n" << rot.real() << "\n";
    cout << "rot_im   is \n" << rot.imag() << "\n";
    cout << "curr_re  is \n" << curr.real() << "\n";
    cout << "curr_im  is \n" << curr.imag() << "\n";
    cout << "ei_re  is \n" << ei.real() << "\n";
    cout << "ei_im  is \n" << ei.imag() << "\n";
    cout << "eprime_re is \n" << eprime.real() << "\n";
    cout << "eprime_im is \n" << eprime.imag() << "\n";
    cout << "v_re  is \n" << V.real() << "\n"; 
    cout << "v_im  is \n" << V.imag() << "\n";
    cout << "E_isat is \n" << E_Isat << "\n"; 
    cout << "fldcur\n" << fld_cur << "\n"; 


    mac_em(bus , mac_con , bus_int , mac_em_idx , i , k , flag, n_em , basmva , mac_pot , 
        eterm , pelect , qelect , phi, psi_re , psi_im , mac_ang, mac_spd , eqprime , vex ,
        edprime , busnum , curqg  , curdg , eq , ed , curq , curd , pmech , theta , V , curr , 
        eprime , ei , rot);

    cout << "out_put for mac_em is--------\n";
    cout << "theta is \n" << theta << "\n";
    cout << "curd is \n" << curd << "\n";
    cout << "curdg is \n" << curdg << "\n";
    cout << "curq is \n" << curq << "\n";
    cout << "curqg is \n" << curqg << "\n";
    cout << "ed is \n" << ed << "\n";
    cout << "edprime is \n" << edprime << "\n";
    cout << "eq is \n" << eq << "\n";
    cout << "eqprime is \n" << eqprime << "\n";
    cout << "etern  is \n" << eterm << "\n";
    cout << "mac_ang  is \n" << mac_ang << "\n";
    cout << "mac_spd  is \n" << mac_spd << "\n";
    cout << "pelect  is \n" << pelect << "\n";
    cout << "qelect  is \n" << qelect << "\n";
    cout << "pmetch  is \n" << pmech << "\n";
    cout << "phi  is \n" << phi << "\n";


    // // // Create placeholders For pss 
    MatrixXd  Tclead1, Tclead2, Tclag1;
    MatrixXd pss1, pss2, pss3, pss_out, dpw_pss_idx, dpw_out;
    
    pss(i, flag, pss_con, Tclead1, Tclead2, Tclag1, pss_idx, pss_pot, mac_int, pss_p_idx, pss_mb_idx, 
    pss_exc_idx, pss1, pss_T4_idx, pss_T4, pss2, pss3, pss_out, dpw_pss_idx, dpw_out, mac_con, 
    mac_spd, pelect, pss_sp_idx, basmva);

    cout << "----------result (pss)----------\n";
    cout << "pss_pot is : \n" << pss_pot << "\n";
    cout << "pss1 is :\n" << pss1 << "\n";
    cout << "pss2 is :\n" << pss2 << "\n";
    cout << "pss3 is :\n" << pss3 << "\n";
    cout << "pss_out is : \n" << pss_out <<"\n"; 


    // palce holders for exc_st3 
    MatrixXd theta1;
    theta1.resize(14, 1);
    theta1 = bus_sol_1.col(2) * (M_PI / 180);

    MatrixXd Efd , V_B , V_R  , V_A , V_As , V_TR , R_f;    
    MatrixXcd iterm , vep , ve;
    MatrixXd F_EX , low_IN , V_I , n_mat , n_bus_mat , V_E , I_N;
    
    exc_st3(i , flag , n_sub , n_tra, exc_con , mac_con , mac_pot , bus_int , mac_int , vex , pelect , qelect , eterm
     , theta1 , fld_cur , Efd , exc_pot , V_B , V_R , V_A , V_As , V_TR , R_f , st3_idx , st3_TB_idx,
        iterm , vep , ve , F_EX , n_mat , n_bus_mat ,low_IN , V_I , V_E , I_N);
    
    cout << "-------------resalt(exc_st3)---------------\n ";
    cout << "iterm is : \n" << iterm << "\n";
    cout << "vep is : \n" << vep << "\n";
    cout << "ve is : \n" << ve << "\n";
    cout << "F_EX is : \n" << F_EX << "\n";
    cout << "n_bus is : \n" << n_bus_mat << "\n";
    cout << "n is : \n" << n_mat << "\n";
    cout << "Efd is : \n" << Efd << "\n";
    cout << "exc_pot is : \n" << exc_pot << "\n";
    cout << "low_IN is : \n" << low_IN << "\n";
    cout << "V_B is : \n" << V_B << "\n";
    cout << "I_N is : \n" << I_N  << "\n";
    cout << "V_E is ; \n" << V_E << "\n";
    cout << "V_R is : \n" << V_R << "\n";
    cout << "V_A is : \n" << V_A << "\n";
    cout << "V_As is : \n" << V_As << "\n";
    cout << "V_I is : \n" << V_I << "\n";
    cout << "V_TR is : \n" << V_TR << "\n";
    cout << "R_f is : \n" << R_f << "\n";    

    // //place holders for tg  ...

    MatrixXd tg_pot , tg1 , tg2 , tg3 , tg_sig , n_tg_mat; 

    tg(i ,flag , mac_int , tg_con , tg_idx ,pmech , n_tg,  tg1 , tg2 , tg3 , tg_pot , tg_sig , n_tg_mat);

    cout << "------------result(tg)-------------\n";
    cout << "tg1 is : \n" << tg1 << "\n";
    cout << "tg_pot is : \n" << tg_pot << "\n";
    cout << "tg2 is : \n" << tg2 << "\n";
    cout << "tg3 is : \n" << tg3 << "\n";
    cout << "tg_sig is : \n" << tg_sig << "\n";
    cout << "n_tg_mat is : \n" << n_tg_mat << "\n";
    cout << "-------------------------\n";

    // ------------------------------------------------------------------------------------------------
    cout << "bus is : \n" << bus << "\n";
    cout << "load_con is :\n" << load_con << "\n";
    // here we should call nc_load  ... 
    MatrixXd j;
    MatrixXcd V_nc , S_cc, load_pot;

    nc_load(bus, flag , load_con , j , V_nc , S_cc , load_pot);

    cout << "-----------result(nc_load)---------\n";
    cout << "V_nc is :\n" << V_nc << "\n";
    cout << "load_pot is :\n" << load_pot << "\n";
    cout << "S_cc is : \n" << S_cc << "\n";
    cout << "j is :\n" << j << "\n";
    
    // double H_sum = 0;
    
    // for(int li = 0; li < n ;++li){
    //     H_sum += mac_con(li ,15) / mac_pot(li , 0);
    // }

    // double kt = 0;
    // double ks = 1;
    // int lswitch = k_inc.rows();

    // double k_tot = 0;
    // for(int li=  0 ;li < lswitch ; ++li){
    //     k_tot += k_inc(li ,0);
    // }

    // double ktmax = k_tot - k_inc(lswitch -1 , 0); // meaning the last element ..
    // MatrixXd bus_sim = bus;
} 
