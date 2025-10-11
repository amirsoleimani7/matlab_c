#include <iostream>
#include "H_header.h"

using namespace std;


int main(){



    Eigen::MatrixXd mac_con(4, 23); // 4 rows and 23 columns

    mac_con << 1, 1, 900, 0.2, 0, 1.8, 0.3, 0.25, 8, 0.03, 1.7, 0.55, 0.24, 0.4, 0.05, 6.5, 0, 0, 1, 0.0654, 0.5743, 1, 1,
               2, 2, 900, 0.2, 0, 1.8, 0.3, 0.25, 8, 0.03, 1.7, 0.55, 0.25, 0.4, 0.05, 6.5, 0, 0, 2, 0.0654, 0.5743, 1, 1,
               3, 6, 900, 0.2, 0, 1.8, 0.3, 0.25, 8, 0.03, 1.7, 0.55, 0.24, 0.4, 0.05, 6.5, 0, 0, 3, 0.0654, 0.5743, 1, 1,
               4, 7, 900, 0.2, 0, 1.8, 0.3, 0.25, 8, 0.03, 1.7, 0.55, 0.25, 0.4, 0.05, 6.5, 0, 0, 4, 0.0654, 0.5743, 1, 1;

    std::cout << "mac_con matrix:\n" << mac_con << std::endl;



    int n_mac = 0;
    MatrixXd mac_pot;

    cout << "before the function \n";

    mac_indx(mac_con ,mac_pot , n_mac);

    cout << "we are out of the function \n";


    return 0;
}