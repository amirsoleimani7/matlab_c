#include <iostream>
#include "H_header.h"

using namespace std;

int main(){
    
    Eigen::MatrixXd mac_con(4, 23);
    mac_con  << 1, 1, 900, 0.2, 0, 1.8, 0.3, 0.25, 8, 0.03, 1.7, 0.55, 0.24, 0.4, 0.05, 6.5, 0, 0, 1, 0.0654, 0.5743, 1, 1,
            2, 2, 900, 0.2, 0, 1.8, 0.3, 0.25, 8, 0.03, 1.7, 0.55, 0.25, 0.4, 0.05, 6.5, 0, 0, 2, 0.0654, 0.5743, 1, 1,
            3, 6, 900, 0.2, 0, 1.8, 0.3, 0.25, 8, 0.03, 1.7, 0.55, 0.24, 0.4, 0.05, 6.5, 0, 0, 3, 0.0654, 0.5743, 1, 1,
            4, 7, 900, 0.2, 0, 1.8, 0.3, 0.25, 8, 0.03, 1.7, 0.55, 0.25, 0.4, 0.05, 6.5, 0, 0, 4, 0.0654, 0.5743, 1, 1;

    std::cout << "Matrix mac_con:\n" << mac_con << std::endl;

    Eigen::MatrixXd exc_con(4, 20);
    exc_con << 3, 1, 0, 7.04, 0.4, 6.67, 1, 7.57, 0, 0.2, -0.2, 200, 4.365, 20, 4.83, 0.091, 1.096, 6.53, 1, 6.53,
               3, 2, 0, 7.04, 0.4, 6.67, 1, 7.57, 0, 0.2, -0.2, 200, 4.365, 20, 4.83, 0.091, 1.096, 6.53, 1, 6.53,
               3, 3, 0, 7.04, 0.4, 6.67, 1, 7.57, 0, 0.2, -0.2, 200, 4.365, 20, 4.83, 0.091, 1.096, 6.53, 1, 6.53,
               3, 4, 0, 7.04, 0.4, 6.67, 1, 7.57, 0, 0.2, -0.2, 200, 4.365, 20, 4.83, 0.091, 1.096, 6.53, 1, 6.53;

    std::cout << "Matrix exc_con:\n" << exc_con << std::endl;

    Eigen::MatrixXd pss_con(4, 10);
    pss_con << 1, 1, 100, 10, 0.05, 0.01, 0.05, 0.01, 0.2, -0.05,
               1, 2, 100, 10, 0.05, 0.01, 0.05, 0.01, 0.2, -0.05,
               1, 3, 100, 10, 0.05, 0.01, 0.05, 0.01, 0.2, -0.05,
               1, 4, 100, 10, 0.05, 0.01, 0.05, 0.01, 0.2, -0.05;

    std::cout << "Matrix pss_con:\n" << pss_con << std::endl;

    Eigen::MatrixXd mac_int(4, 1);
    mac_int << 1, 2, 3, 4;

    std::cout << "MatriX mac_int:\n" << mac_int << std::endl;


    MatrixXd pss_pot; 
    MatrixXd pss_idx, pss_sp_idx, pss_p_idx, pss_mb_idx ,pss_exc_idx;
    MatrixXd pss_T, pss_T2 ,pss_T4 ,pss_T4_idx , pss_noT4_idx ,pss_noT4;

    int n_pss;
    
    
    pss_indx(pss_con , mac_con, exc_con,pss_idx , n_pss , pss_sp_idx , pss_p_idx , pss_mb_idx , pss_exc_idx , 
            pss_T , pss_T2 , pss_T4 , pss_T4_idx , pss_noT4);

    cout << "we are after the function pss_indx\n";

    return 0;
}