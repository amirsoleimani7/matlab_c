#include "../include/H_header.h"

using namespace Eigen;
using namespace std;


void tg(int i, int flag, 
    MatrixXd &mac_int, 
    MatrixXd &tg_con, 
    MatrixXd &tg_idx, 
    MatrixXd &pmech, 
    int n_tg,
    MatrixXd &tg1,
    MatrixXd &tg2,
    MatrixXd &tg3,
    MatrixXd &tg_pot,
    MatrixXd &tg_sig,
    MatrixXd &n_tg_mat)
{
    int k = 0; // this should be given to the user  ... 

    complex<float> jay(0.0, 1.0); // the is the sqrt(-1)
    
    tg1.resize(n_tg , 1);
    tg2.resize(n_tg , 1);
    tg3.resize(n_tg , 1);
 
    tg_pot.resize(n_tg ,5);
    MatrixXd a1(n_tg , 1);
    MatrixXd a2(n_tg , 1);
    
    MatrixXd T3(n_tg , 1);
    MatrixXd T4(n_tg , 1);
    MatrixXd T5(n_tg , 1);
    MatrixXd Tc(n_tg , 1);

    n_tg_mat.resize(0 ,1); // will change dynamicly 
    tg_sig.resize(n_tg , 1);

    if(flag == 0 && i == 0){

        for(int li = 0 ; li < n_tg ;li ++){

            int lj = tg_idx(li , 0) - 1;

            int n = mac_int((int)tg_con(lj , 1) -1) -1; // we should take the machine number ... machines that have governer-turbine
            n_tg_mat.conservativeResize(n_tg_mat.rows() +1  ,NoChange);
            n_tg_mat(n_tg_mat.rows() -1 , 0) = n + 1;
            // this is for the scaler one .. (but needs to be checked for vectorized as well)
            if (pmech(n, 0) > tg_con(lj, 4)) {   // the indexing needs to be checked ...  // not sure about the indexing of the pmech(lj , 1) or pmetch(lj , k)
                cout << "TG init: pmech > upper limit, check machine base";
            }

            if (pmech(n, 0) < 0) { //should'nt be less than 0 either
                cout << "TG init: pmech < 0, check data";
            }

            tg1(lj , 0) = pmech(n, 0);


            tg_pot(lj, 0) = tg_con(lj ,7) / tg_con(lj , 6); // just same as the matlab code 

                        
            a1(lj, 0) = 1 - tg_pot(lj, 0);

            tg_pot(lj, 1) = a1(lj , 0); 

            tg2(lj, 0) = a1(lj , 0) * pmech(n, k); // not sure about the pmech(n ,k / 0)  

            // tg_pot(lj , 2) = T4(lj , 0) / T5(lj , 0);    
            tg_pot(lj , 2) = tg_con(lj , 8) /tg_con(lj , 9); // we may need to subsitute this line 
            
            a2(lj , 0) = 1 - tg_pot(lj, 2);

            tg_pot(lj, 3) = a2(lj ,0);

            tg3(lj, 0) = a2(lj ,0) * pmech(n, k); 

            tg_pot(lj, 4) = pmech(n, k);
            
            tg_sig(lj, 0) = 0;

        }
    }
}