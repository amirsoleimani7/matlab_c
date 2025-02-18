#include "../include/H_header.h"

using namespace Eigen;
using namespace std;

void pss_indx(MatrixXd& pss_con, MatrixXd& mac_con, MatrixXd& exc_con, 
              MatrixXd& pss_idx, int& n_pss, MatrixXd& pss_sp_idx, 
              MatrixXd& pss_p_idx, MatrixXd& pss_mb_idx, MatrixXd& pss_exc_idx, 
              MatrixXd& pss_T, MatrixXd& pss_T2, MatrixXd& pss_T4, 
              MatrixXd& pss_T4_idx, MatrixXd& pss_noT4) {


    cout << "we ARE in the function \n";
    int _globjpss = 0;

    if (pss_con.rows() > 0) {
        pss_idx.resize(0 , 1);

        for (int i = 0; i < pss_con.rows(); ++i) { // if speed or power
                if (pss_con(i, 0) == 1 || pss_con(i, 0) == 2) {
                    pss_idx.conservativeResize(pss_idx.rows() +1 , NoChange);
                    pss_idx(pss_idx.rows() -1, 0) = i + 1;
                }
        }

      

        n_pss = pss_idx.rows();
        pss_mb_idx.resize(n_pss, 1);

        for(int i = 0 ; i < n_pss ; ++i){
            pss_mb_idx(i, 0) = int((int)pss_con(i , 1)); // Convert to zero-based index //no need for pss_con i think  ... 
        }



        pss_exc_idx.resize(0 ,1);

        for (int jpss = 0; jpss < n_pss; ++jpss) {
            for (int k = 0; k < exc_con.rows(); ++k) {

                if ((pss_con((int)pss_idx(jpss, 0) - 1, 1)) == (exc_con(k, 1))) {
                    pss_exc_idx.conservativeResize(pss_exc_idx.rows() + 1 , NoChange);
                    pss_exc_idx(pss_exc_idx.rows() -1 , 0) = k + 1 ;
                }   
            }   
            _globjpss = jpss ;
        }

        if(pss_exc_idx.size() == 0){
            cout << "you must have an exciter at the same generator as a pss\n";
        }




        // init the pss_T , pss_T2  , pss_T4
        if (n_pss != 0) {

            pss_T.resize(n_pss, 1);
            pss_T2.resize(n_pss, 1);
            pss_T4.resize(n_pss, 1);
            
            for(int i = 0 ; i < n_pss ; ++i){
                pss_T(i, 0) = pss_con((int)pss_idx(i, 0) -1, 3); // generatorNo
                pss_T2(i, 0) = pss_con((int)pss_idx(i, 0) -1, 5); // Twasshot 
                pss_T4(i, 0) = pss_con((int)pss_idx(i, 0) -1, 7); // Tclag2
            }

            pss_T4_idx.resize(0 ,1);
            pss_noT4.resize(0 ,1);


            for(int i = 0 ; i < n_pss ; ++i){

                if(pss_T4(i , 0) > .001){
                    pss_T4_idx.conservativeResize(pss_T4_idx.rows() + 1 , NoChange);
                    pss_T4_idx(pss_T4_idx.rows() -1 , 0) = i + 1;
                }
                
                if(pss_T4(i , 0) < .001){
                    pss_noT4.conservativeResize(pss_noT4.rows() + 1 , NoChange);
                    pss_noT4(pss_noT4.rows() -1 , 0) = i + 1;
                }                                
            }

        

            pss_sp_idx.resize(0 ,1);
            pss_p_idx.resize(0 ,1);
        
            for(int i = 0 ; i < n_pss ; ++i){
                
                if(pss_con((int)pss_idx(i , 0) -1  , 0) == 1){
                    pss_sp_idx.conservativeResize(pss_sp_idx.rows() +1 , NoChange);
                    pss_sp_idx(pss_sp_idx.rows() - 1 , 0) = i + 1;
                }

                if(pss_con((int)pss_idx(i , 0)-1 , 0) == 2){
                    pss_p_idx.conservativeResize(pss_p_idx.rows() +1 , NoChange);
                    pss_p_idx(pss_p_idx.rows() - 1 , 0) = i + 1;
                }

            }
        }
    }
    


            // cout << "pss_idx is : \n "<< pss_idx <<"\n";   
            // cout << "pss_mb_idx is : \n" << pss_mb_idx <<"\n";
            // cout << "pss_con is : \n" << pss_con <<"\n";
            // cout << "pss_exc_idx is : \n" << pss_exc_idx <<"\n";
            // cout << "exc_con is : \n" << exc_con  <<"\n ";
            // cout << "pss_exc_idx is : \n" << pss_exc_idx << "\n";
            // cout << "pss_T is : \n" << pss_T << "\n";
            // cout << "pss_T2 is : \n" << pss_T2 << "\n";
            // cout << "pss_T4 is : \n" << pss_T4 << "\n";
            // cout << "pss_T4_idx is : \n" << pss_T4_idx << "\n";
            // cout << "pss_noT4 is : \n" << pss_noT4 << "\n";
            // cout << "pss_sp_idx is : \n" << pss_sp_idx << "\n"; 
            // cout << "pss_p_idx is : \n" << pss_p_idx << "\n";


            // cout << "jpss : "<< _globjpss +1 << "\n";
            // cout << "n_pss : " << n_pss << "\n";
            
}
