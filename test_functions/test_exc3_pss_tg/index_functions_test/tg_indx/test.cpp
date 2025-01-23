#include <iostream>
#include "H_header.h"

using namespace std;

int main(){


        Eigen::MatrixXd tg_con(4, 10); 

        tg_con << 1, 1, 1, 25, 1, 0.1, 0.5, 0, 1.25, 5,
                1, 2, 1, 25, 1, 0.1, 0.5, 0, 1.25, 5,
                1, 3, 1, 25, 1, 0.1, 0.5, 0, 1.25, 5,
                1, 4, 1, 25, 1, 0.1, 0.5, 0, 1.25, 5;

        std::cout << "tg_con matrix:\n" << tg_con << std::endl;


        MatrixXd tg_idx , tgh_idx;
        int n_tg, n_tgh ;
        Tg_idx(tg_con , tg_idx , n_tg , tgh_idx , n_tg);

    return 0;
}