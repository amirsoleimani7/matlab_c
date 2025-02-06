#include "H_header.h"

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

    //result of the load_flow
    cout << "bus_sol_1 is : \n" << bus_sol_1 << "\n";
    cout << "line_sol_1 is : \n" << line_sol_1 << "\n";
    cout << "line_flow_1 is : \n" << line_flow_1 << "\n";
    

    // set indexes 
    // note : dc index set in dc load flow


    // init matrixes for the mac_indx 
    MatrixXd mac_pot , mac_em_idx , mac_tra_idx , mac_sub_idx , mac_int;
    int macmax, n_tot , n_ig , n_em , n_tra, n_sub ;
    int n_mac = 0;

    mac_indx(mac_con , mac_pot , mac_em_idx , mac_tra_idx , mac_sub_idx , mac_int
            ,macmax , n_mac , n_tot , n_ig, n_em , n_tra ,n_sub);

    //mac_indx result 
    cout << "mac_em_idx is :\n" << mac_em_idx <<"\n";
    cout << "mac_tra_idx is : \n" << mac_tra_idx <<"\n";
    cout << "mac_sub_idx is  : \n" << mac_sub_idx <<"\n";
    cout << "mac_int is : \n " << mac_int <<"\n";
    cout << "macmax is : " << macmax << "\n";
    cout << "n_mac is : " << n_mac <<"\n";
    cout << "n_tot is : " << n_tot << "\n";
    cout << "n_ig is : " << n_ig << "\n";
    cout << "n_em is : " << n_em <<"\n";
    cout << "n_tra is : " << n_tra <<"\n";
    cout << "n_sub is : " << n_sub <<"\n";
    
    //init matrixes for exc_indx
    MatrixXd st3_idx , st3_TA , st3_TA_idx , st3_noTA_idx;
    MatrixXd exc_pot , st3_TB , st3_TB_idx , st3_noTB_idx , st3_TR , st3_TR_idx ,st3_noTR_idx;
    int n_exc , n_st3;

    exc_indx(exc_con , exc_pot , n_exc , st3_idx , n_st3 , st3_TA , st3_TA_idx ,st3_noTA_idx
            ,st3_TB , st3_TB_idx , st3_noTB_idx , st3_TR , st3_TR_idx , st3_noTR_idx);


    //exc_indx result
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

    
    //init matrixes for tg_indx
    MatrixXd tg_idx , tgh_idx;
    int n_tg, n_tgh ;
    Tg_idx(tg_con , tg_idx , n_tg , tgh_idx , n_tgh);

    //tg_indx result 
    cout << "n_tg is : " << n_tg << "\n"; 
    cout << "n_tgh is : " << n_tgh << "\n";
    cout << "tg_idx is : \n" << tg_idx << "\n";
    cout << "tgh_idx is : \n" << tgh_idx <<  "\n";    


    //init matrixes for pss_indx    

    MatrixXd pss_pot; 
    MatrixXd pss_idx, pss_sp_idx, pss_p_idx, pss_mb_idx ,pss_exc_idx;
    MatrixXd pss_T, pss_T2 ,pss_T4 ,pss_T4_idx , pss_noT4_idx ,pss_noT4;

    int n_pss;
    
    pss_indx(pss_con , mac_con, exc_con,pss_idx , n_pss , pss_sp_idx , pss_p_idx , pss_mb_idx , pss_exc_idx , 
            pss_T , pss_T2 , pss_T4 , pss_T4_idx , pss_noT4);

    
    //pss_indx result 
     cout << "pss_idx is : \n "<< pss_idx <<"\n";   
    cout << "pss_mb_idx is : \n" << pss_mb_idx <<"\n";
    cout << "pss_con is : \n" << pss_con <<"\n";
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







} 


//     MatrixXd mac_indx,exc_indx,tg_indx,pss_indx; //initiallizaation
    
//     double n_tot = n_mac;
//     double ngm = n_mac;
//     double n_pm = n_mac;

//     double k = 1;

//     double n_switch = sw_con.rows();

//     MatrixXd k_inc = MatrixXd::Zero(n_switch -1 , 1);
//     MatrixXd t = MatrixXd::Zero(n_switch -1 , 1);
//     MatrixXd t_switch = MatrixXd::Zero(n_switch -1 , 1);
//     MatrixXd h = t_switch;


//     for (int li = 0; li < n_switch - 1; ++li) {
//         h(li) = sw_con(li, 6);
        
//         if (sw_con(li, 6) == 0){
//             h(li) = 0.01;
//         }

//         k_inc(li) = std::floor((sw_con(li + 1, 0) - sw_con(li, 0)) / h(li)); 
        
//         if (k_inc(li) == 0) {
//             k_inc(li) = 1;  // minimum 1
//         }

//         h(li) = (sw_con(li + 1, 0) - sw_con(li, 0)) / k_inc(li);  // step length

//         t_switch(li + 1) = t_switch(li) + k_inc(li) * h(li);

//         for(int lj = 0; lj < k_inc(li);++lj){
//             double i1 = k + lj;
//             double i2 = li + h(li) * lj; // not sure abount this at all ...
//             t_switch((int)i2) = i2;
//             t((int)i1) = i1;
//         }
//         k = k_inc(li) + k;
//     }

//     k = k +1 ;
//     t(k) = sw_con(n_switch -1 ,0);
//     double n = mac_con.rows();
    
//     MatrixXd z = MatrixXd::Zero(n ,k);
//     MatrixXd z1 = MatrixXd::Zero(1 ,k);
//     MatrixXd theta = MatrixXd::Zero(bus.rows() +1 ,k);
//     MatrixXd bus_v = MatrixXd::Zero(bus.rows() +1 ,k);
//     MatrixXd z_tg = MatrixXd::Zero(1 ,k);
    
// }