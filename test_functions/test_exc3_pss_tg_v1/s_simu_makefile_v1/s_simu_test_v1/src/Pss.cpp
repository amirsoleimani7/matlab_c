#include "../include/H_header.h"

using namespace std;
using namespace Eigen;


void pss(int i, int flag, MatrixXd& pss_con,MatrixXd& Tclead1, MatrixXd& Tclead2 , MatrixXd Tclag1 ,MatrixXd& pss_idx,MatrixXd& pss_pot,MatrixXd& mac_int,MatrixXd& pss_p_idx , MatrixXd& pss_mb_idx, MatrixXd& pss_exc_idx,
         MatrixXd& pss1, MatrixXd& pss_T4_idx , MatrixXd& pss_T4,MatrixXd& pss2, MatrixXd& pss3, MatrixXd& pss_out, MatrixXd& dpw_pss_idx, 
         MatrixXd& dpw_out, MatrixXd& mac_con, MatrixXd& mac_spd, MatrixXd& pelect, MatrixXd& pss_sp_idx ,double basmva) {
  
    
    int f = 0;
    int n_pss =  pss_idx.rows();

    if (n_pss != 0) {        

        if (i != 0) {
            if (pss_con(i, 0) != 1 && pss_con(i, 0) != 2) { //they should be 1 or 2 .. 
                cout << "PSS: inappropriate power system stabilizer model" << endl;
                exit(0);
            }
        }

        complex<double> jay(0, 1);
        int num_mac = mac_con.rows();

        if (flag == 0) { // initialization // vector computation mode 
            if(i == 0){
                pss_pot = MatrixXd::Ones(n_pss, 2);

                MatrixXd n = pss_mb_idx; // same as the pss_mb_idx
                MatrixXd n_sp(pss_sp_idx.rows() , 1);

                n_sp.resize(pss_sp_idx.rows() ,1);
                pss1.resize(pss_sp_idx.rows() ,1);
                

                if (pss_sp_idx.rows() != 0) {
                    for(int li = 0; li < pss_sp_idx.rows() ; ++li){
                        n_sp(li , 0) =  mac_int((int)pss_con((int)pss_sp_idx(li ,0) -1, 1) -1 ,0);
                        pss1((int)pss_sp_idx(li , 0) -1, 0) = mac_spd((int)n_sp(li , 0) -1, 0);
                    }   
                }
            
                MatrixXd n_p(pss_idx.rows() , 1);

                if (pss_p_idx.rows() != 0) {
                    for(int li = 0; li < pss_p_idx.rows() ; ++li){
                        n_p(li , 0) = mac_int((int)pss_con((int)pss_p_idx(li , 0) -1, 1) -1 , 0) -1 ;
                        pss1((int)pss_p_idx(li , 0) -1, 0) = (pelect((int)n_p(li , 0), 0) * basmva )/ mac_con((int)n_p(li , 0), 2);
                    }   
                }

                // if (dpw_pss_idx.rows() != 0) { // not sure about this dude ... 
                //     pss1(dpw_pss_idx, 0) = dpw_out.col(0);
                // }
                
                pss2.resize(n_pss ,1);
                pss2.setZero();
                pss3.resize(n_pss ,1);
                pss3.setZero();
                pss_out.resize(4 ,1);
                pss_out.setZero();

                for(int li = 0 ; li < n_pss ;++li){
                    pss2((int)pss_idx(li , 0) -1) = 0;
                    pss3((int)pss_idx(li , 0) -1) = 0;
                    pss_out((int)pss_exc_idx(li , 0) -1) = 0;                    
                    pss_pot(li , 0) = pss_con(li , 4) / pss_con(li , 5);  
                }   
                
                for(int li = 0 ;li < pss_T4_idx.rows() ;++li){
                    pss_pot((int)pss_T4_idx(li , 0) -1, 1) = pss_con((int)pss_T4_idx(li , 0) -1, 6) / pss_T4((int)pss_T4_idx(li, 0)-1 , 0);                    
                }
            }
        }
    }
}