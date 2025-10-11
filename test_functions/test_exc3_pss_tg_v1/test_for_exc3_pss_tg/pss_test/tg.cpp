#include "H_header.h"

using namespace Eigen;
using namespace std;



MatrixXd basmva;
MatrixXd mac_int;
MatrixXd mac_con;
MatrixXd pelect;
MatrixXd pmech;
MatrixXd mac_spd;
MatrixXd tg_con;
MatrixXd tg_pot;
MatrixXd tg1;
MatrixXd tg2;
MatrixXd tg3;
MatrixXd dtg1;
MatrixXd T3;
MatrixXd T4;
MatrixXd T5;
MatrixXd Tc;

MatrixXd a1;
MatrixXd a2;

MatrixXd dtg3;
VectorXi tg_idx;

int n_tg;
int k; // described as integer time .. .
MatrixXd tg_sig;

//k comes from  the s_simu function ... 

void tg(int k, const MatrixXd& bus, int flag) {

    complex<float> j(0.0, 1.0);

    for(int li = 0 ; li < n_tg ;li ++){

        int lj = tg_idx(li , 0);

        int n = mac_int((int)tg_con(lj , 1)); // we should take the machine number ... 

        if (pmech(n, k) > tg_con(lj, 4)) {   // the indexing needs to be checked ... 
            cout << "TG init: pmech > upper limit, check machine base";
        }

        if (pmech(n, k) < 0) {
            cout << "TG init: pmech < 0, check data";
        }
        
        tg1(lj , 0) = pmech(n, 0);

        tg_pot(lj, 0) = T3(lj ,0) / Tc(lj , 0);
        
        a1(lj, 0 ) = 1 - tg_pot(lj, 0);

        tg_pot(lj, 1) = a1(lj , 0);

        tg_pot(lj , 2) = T4(lj , 0) / T5(lj , 0);
    
        tg2(lj, 0) = a1(lj , 0) * pmech(n, k);
        
        a2(lj , 0) = 1 - tg_pot(lj, 2);

        tg_pot(lj, 3) = a2(lj ,0);

        tg3(lj, 0) = a2(lj ,0) * pmech(n, k);

        tg_pot(lj, 4) = pmech(n, k);
        
        tg_sig(lj, 0) = 0;

    }

}
