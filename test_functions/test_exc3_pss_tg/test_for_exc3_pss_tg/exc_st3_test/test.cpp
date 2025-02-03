#include <iostream>
#include "H_header.h"

using namespace std;


int main()
{
    // this is the test_function for exc_st3 funtion ..
        
    Eigen::MatrixXd mac_con(4, 23);
    mac_con << 1, 1, 900, 0.2, 0, 1.8, 0.3, 0, 8, 0.03, 1.7, 0.3, 0.24, 0.4, 0.05, 6.5, 0, 0, 1, 0.0654, 0.5743, 1, 1,
               2, 2, 900, 0.2, 0, 1.8, 0.3, 0, 8, 0.03, 1.7, 0.3, 0.25, 0.4, 0.05, 6.5, 0, 0, 2, 0.0654, 0.5743, 1, 1,
               3, 6, 900, 0.2, 0, 1.8, 0.3, 0, 8, 0.03, 1.7, 0.3, 0.24, 0.4, 0.05, 6.5, 0, 0, 3, 0.0654, 0.5743, 1, 1,
               4, 7, 900, 0.2, 0, 1.8, 0.3, 0, 8, 0.03, 1.7, 0.3, 0.25, 0.4, 0.05, 6.5, 0, 0, 4, 0.0654, 0.5743, 1, 1;

    std::cout << "mac_con matrix:\n" << mac_con << "\n";

    Eigen::MatrixXd mac_int(4, 1);
    mac_int << 1, 2, 3, 4;

    std::cout << "mac_int matrix:\n" << mac_int << std::endl;

    Eigen::MatrixXd exc_con(4, 20);
    exc_con << 3, 1, 0, 300, 0.4, 6.67, 1, 7.57, 0, 0.2, -0.2, 200, 4.365, 20, 4.83, 0.091, 1.096, 40, 1, 6.53,
               3, 2, 0, 300, 0.4, 6.67, 1, 7.57, 0, 0.2, -0.2, 200, 4.365, 20, 4.83, 0.091, 1.096, 40, 1, 6.53,
               3, 3, 0, 300, 0.4, 6.67, 1, 7.57, 0, 0.2, -0.2, 200, 4.365, 20, 4.83, 0.091, 1.096, 40, 1, 6.53,
               3, 4, 0, 300, 0.4, 6.67, 1, 7.57, 0, 0.2, -0.2, 200, 4.365, 20, 4.83, 0.091, 1.096, 40, 1, 6.53;

    std::cout << "exc_con matrix:\n" << exc_con << std::endl;


    Eigen::MatrixXd st3_idx(4, 1);
    st3_idx << 1, 2, 3, 4;

    std::cout << "st3_idx matrix:\n" << st3_idx << std::endl;

    Eigen::MatrixXd bus_int(13, 1);
    bus_int << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13;

    std::cout << "bus_int matrix:\n" << bus_int << std::endl;

    Eigen::MatrixXd vex(4, 1);
    vex << 1.87245065830439, 
           1.95024192439475, 
           1.81514178352559, 
           1.91659268284482;

    std::cout << "vex matrix:\n" << vex << std::endl;

    Eigen::MatrixXd pelect(4, 1);
    pelect << 7.26106622019356, 
              7, 
              7, 
              7;

    std::cout << "pelect matrix:\n" << pelect << std::endl;

    Eigen::MatrixXd qelect(4, 1);
    qelect << 1.27119216215814, 
              1.94200544624984, 
              1.13415163866497, 
              1.76305806835366;

    std::cout << "qelect matrix:\n" << qelect << std::endl;

    Eigen::MatrixXd eterm(4, 1);
    eterm << 1.01, 1.01, 1.01, 1.01 ;

    std::cout << "eterm matrix:\n" << eterm << std::endl;

    Eigen::MatrixXd theta(14, 1);
    theta <<  0.322885911618951, 
              0.134825139650961, 
             -0.129863257254776, 
             -0.17857604175599, 
              0.2020801912147, 
             -0.157298115763022, 
             -0.333711889371994, 
             -0.594510944060937, 
             -0.681034322781182, 
              0.0170136892433736, 
             -0.367460704798512, 
             -0.273536351796361, 
             -0.451171213764415, 
              0;

    std::cout << "theta matrix:\n" << theta << std::endl;    

    Eigen::MatrixXd mac_pot(4, 15);
    mac_pot << 0.111111111111111, 1, 6.9795, -11.2361, 5.32200000000001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0.111111111111111, 1, 6.9795, -11.2361, 5.32200000000001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0.111111111111111, 1, 6.9795, -11.2361, 5.32200000000001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0.111111111111111, 1, 6.9795, -11.2361, 5.32200000000001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;

    std::cout << "mac_pot matrix:\n" << mac_pot << std::endl;


    Eigen::MatrixXd fldcur(4, 1);
    fldcur << 1.87245065830439, 
              1.95024192439475, 
              1.81514178352559, 
              1.91659268284482;

    std::cout << "fldcur matrix:\n" << fldcur << std::endl;


    Eigen::MatrixXd st3_TB_idx(4, 1);
    st3_TB_idx << 1, 2, 3, 4;

    std::cout << "st3_TB_idx matrix:\n" << st3_TB_idx << std::endl;

    int n_st3 = 4;

    MatrixXd Efd , exc_pot , V_B , V_R , V_A , V_As , V_TR , R_f;

    cout << "this is before the function is called\n";

    
    exc_st3(
        exc_con, mac_con,mac_pot, bus_int, 
        mac_int, vex, pelect, 
        qelect, eterm, theta, 
        fldcur, Efd, exc_pot, 
        V_B, V_R , V_A, V_As, 
        V_TR, R_f, st3_idx, 
        st3_TB_idx);

    cout << "this is after the function \n";



}
