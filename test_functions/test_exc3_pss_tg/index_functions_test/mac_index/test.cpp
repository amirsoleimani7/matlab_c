#include <iostream>
#include "H_header.h"

using namespace std;


int main(){

    Eigen::MatrixXd exc_con(4, 20);
    exc_con << 3, 1, 0, 7.04, 0.4, 6.67, 1, 7.57, 0, 0.2, -0.2, 200, 4.365, 20, 4.83, 0.091, 1.096, 6.53, 1, 6.53,
               3, 2, 0, 7.04, 0.4, 6.67, 1, 7.57, 0, 0.2, -0.2, 200, 4.365, 20, 4.83, 0.091, 1.096, 6.53, 1, 6.53,
               3, 3, 0, 7.04, 0.4, 6.67, 1, 7.57, 0, 0.2, -0.2, 200, 4.365, 20, 4.83, 0.091, 1.096, 6.53, 1, 6.53,
               3, 4, 0, 7.04, 0.4, 6.67, 1, 7.57, 0, 0.2, -0.2, 200, 4.365, 20, 4.83, 0.091, 1.096, 6.53, 1, 6.53;

    std::cout << "exc_con:\n" << exc_con << std::endl;



    MatrixXd st3_idx , st3_TA , st3_TA_idx , st3_noTA_idx;
    MatrixXd exc_pot , st3_TB , st3_TB_idx , st3_noTB_idx , st3_TR , st3_TR_idx ,st3_noTR_idx;
    int n_exc , n_st3;

    cout << "we are before the fucntion \n ";

    exc_indx(exc_con, exc_pot,n_exc, 
                st3_idx,  n_st3,
               st3_TA,  st3_TA_idx, st3_noTA_idx,
              st3_TB,  st3_TB_idx,  st3_noTB_idx,
              st3_TR,  st3_TR_idx,  st3_noTR_idx);
    
    cout << "we are at the end \n";

    return 0;
}