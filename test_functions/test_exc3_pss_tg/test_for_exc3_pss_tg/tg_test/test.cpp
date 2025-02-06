#include <iostream>
#include "H_header.h"

using namespace std;


int main()
{
    // this is the test_function for the tg function
    Eigen::MatrixXd mac_int(4, 1);
    mac_int << 1,
            2,
            3,
            4;
    
    cout << "mac_int is : \n" << mac_int << "\n";

    Eigen::MatrixXd tg_con(4, 10);
    tg_con << 1.000, 1.000, 1.020, 4.000, 2.000, 0.200, 0.050, 0.010, 0.010, 0.010,
            1.000, 2.000, 1.020, 4.000, 2.000, 0.200, 0.050, 0.010, 0.010, 0.010,
            1.000, 3.000, 1.020, 4.000, 2.000, 0.200, 0.050, 0.010, 0.010, 0.010,
            1.000, 4.000, 1.020, 4.000, 2.000, 0.200, 0.050, 0.010, 0.010, 0.010;


    cout << "tg_con is : \n" << tg_con << "\n";

    Eigen::MatrixXd tg_idx(4, 1);
    tg_idx << 1,
            2,
            3,
            4;
    
    cout << "tg_idx is : \n" << tg_idx << "\n";


    Eigen::MatrixXd pmech(4, 1);
    pmech << 0.77930,
            0.77941,
            0.79992,
            0.77936;
        
    cout << "pmech is : \n" << pmech << "\n";

    int n_tg =  4;


    //void tg(MatrixXd &mac_int , MatrixXd &tg_con ,MatrixXd &tg_idx , MatrixXd &pmech , int n_tg);


    cout << "this is before the function .., \n";

    tg(mac_int , tg_con , tg_idx , pmech , n_tg);

    cout << "this is after the function \n";













}
