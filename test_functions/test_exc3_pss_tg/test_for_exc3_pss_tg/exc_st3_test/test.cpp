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

    










}
