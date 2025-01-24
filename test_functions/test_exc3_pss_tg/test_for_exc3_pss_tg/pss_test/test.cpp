#include <iostream>
#include "H_header.h"

using namespace std;


int main()
{

    Eigen::MatrixXd pss_mb_idx(4, 1);
    pss_mb_idx << 1,
                  2,
                  3,
                  4;

    std::cout << "pss_mb_idx:\n" << pss_mb_idx << std::endl;

    Eigen::MatrixXd pss_sp_idx(4, 1);
    pss_sp_idx << 1,
                  2,
                  3,
                  4;

    std::cout << "pss_sp_idx:\n" << pss_sp_idx << std::endl;


    Eigen::MatrixXd mac_int(4, 1);
    mac_int << 1,
                  2,
                  3,
                  4;

    std::cout << "mac_int:\n" << mac_int << std::endl;


    Eigen::MatrixXd mac_spd(4, 1);
    mac_spd << 1,
                  1,
                  1,
                  1;

    std::cout << "mac_spd:\n" << mac_spd << std::endl;

    
    Eigen::MatrixXd pelect(4, 1);
    pelect << 7.26106622019356,
                  7,
                  7,
                  7;

    std::cout << "pelect:\n" << pelect << std::endl;

    Eigen::MatrixXd pss_idx(4, 1);
    pss_idx << 1,
                  2,
                  3,
                  4;

    std::cout << "pss_idx:\n" << pss_idx << std::endl;

    Eigen::MatrixXd pss_exc_idx(1, 4);
    pss_exc_idx << 1,
                  2,
                  3,
                  4;

    std::cout << "pss_exc_idx:\n" << pss_exc_idx << std::endl;


    Eigen::MatrixXd pss_T4_idx(4, 1);
    pss_T4_idx << 1,
                  2,
                  3,
                  4;

    std::cout << "pss_T4_idx:\n" << pss_T4_idx << std::endl;

    

    Eigen::MatrixXd pss_T4(4, 1);
    pss_T4 << .01,
                  .01,
                  .01,
                  .01;

    std::cout << "pss_T4:\n" << pss_T4 << std::endl;
    

    int n_pss = 4;
    int i = 0;
    int basmva = 100;
    int flag = 0;
    // Create placeholders
    MatrixXd pss_con, Tclead1, Tclead2, Tclag1, pss_pot, pss_p_idx;
    MatrixXd pss1, pss2, pss3, pss_out, dpw_pss_idx, dpw_out, mac_con;


    cout << "this is before the function\n";

    // pss(i, flag, pss_con, Tclead1, Tclead2, Tclag1, pss_idx, pss_pot, mac_int, pss_p_idx, pss_mb_idx, 
    //     pss_exc_idx, pss1, pss_T4_idx, pss_T4, pss2, pss3, pss_out, dpw_pss_idx, dpw_out, mac_con, 
    //     mac_spd, pelect, pss_sp_idx, basmva);

    cout << "we are  after the function here \n";










}
