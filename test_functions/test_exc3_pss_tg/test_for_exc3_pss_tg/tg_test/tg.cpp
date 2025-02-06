#include "H_header.h"

using namespace Eigen;
using namespace std;



void tg(MatrixXd &mac_int , MatrixXd &tg_con ,MatrixXd &tg_idx , MatrixXd &pmech , int n_tg) { 

    cout << "we are in the tg function \n";


    int flag = 0 , i = 0;
    int k = 0; // this should be given to the user  ... 

    complex<float> jay(0.0, 1.0); // the is the sqrt(-1)
    
    MatrixXd tg1(n_tg , 1);
    MatrixXd tg2(n_tg , 1);
    MatrixXd tg3(n_tg , 1);



    MatrixXd tg_pot(n_tg ,5);
    MatrixXd a1(n_tg , 1);
    MatrixXd a2(n_tg , 1);

    MatrixXd T3(n_tg , 1);
    MatrixXd T4(n_tg , 1);
    MatrixXd T5(n_tg , 1);
    MatrixXd Tc(n_tg , 1);

    MatrixXd tg_sig(n_tg , 1);


    if(flag == 0 && i == 0){

        for(int li = 0 ; li < n_tg ;li ++){

            int lj = tg_idx(li , 0) - 1;

            int n = mac_int((int)tg_con(lj , 1) -1) -1; // we should take the machine number ... machines that have governer-turbine

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
    
    cout << "------------result-------------\n";
    cout << "tg1 is : \n" << tg1 << "\n";
    cout << "tg_pot is : \n " << tg_pot << "\n";
    cout << "tg2 is : \n " << tg2 << "\n";
    cout << "tg3 is : \n" << tg3 << "\n";
    cout << "tg_sig is : \n " <<  tg_sig  << "\n";


     0.2   ,  0.8,       1,       0,  0.7793
    0.2    , 0.8   ,    1   ,    0, 0.77941
    0.2    , 0.8  ,     1  ,     0, 0.79992
    0.2    , 0.8    ,   1    ,   0, 0.77936







}
