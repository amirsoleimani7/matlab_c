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
    
    double n_mac = 0; //not sure need's to be definded ... 

    double tol = 1e-8;

    double iter_max = 30;
    
    double acc = 1.0;
    
    double flag = 1;
    // double flag = 2; // why 2?
    string display = "n";


    MatrixXd bus_sol_1,line_sol_1,line_flow_1; // the bus_sol_1 sould e the same as bus
    load_flow(bus,line,tol,iter_max,acc,display,flag,bus_sol_1,line_sol_1,line_flow_1);

    cout << "bus_sol_1 is : \n" << bus_sol_1 << "\n";
    cout << "line_sol_1 is : \n" << line_sol_1 << "\n";
    cout << "line_flow_1 is : \n" << line_flow_1 << "\n";


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