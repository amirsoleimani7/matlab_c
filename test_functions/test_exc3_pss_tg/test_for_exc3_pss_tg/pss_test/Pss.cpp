#include "H_header.h"

using namespace std;
using namespace Eigen;


void pss(int i, int flag, MatrixXd& pss_con, MatrixXd& pss_pot,MatrixXd& mac_int,MatrixXd& pss_p_idx , MatrixXd& pss_mb_idx, MatrixXd& pss_exc_idx,
         MatrixXd& pss1, MatrixXd& pss2, MatrixXd& pss3, MatrixXd& pss_out, MatrixXd& dpw_pss_idx, 
         MatrixXd& dpw_out, MatrixXd& mac_con, MatrixXd& mac_spd, MatrixXd& pelect, MatrixXd& pss_sp_idx ,double basmva) {
  
    int f = 0;
    int n_pss = pss_con.rows();
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

                cout << "pss_pot is : \n" << pss_pot << "\n"; 

                MatrixXd n = pss_mb_idx; // same as the pss_mb_idx
                MatrixXd n_sp(pss_sp_idx.rows() , 1);

                if (pss_sp_idx.rows() != 0) {
                    for(int li = 0; li < pss_sp_idx.rows() ; ++li){
                        n_sp(li , 0) = mac_int((int)pss_con((int)pss_sp_idx(li ,1), 0) ,2);
                        pss1(pss_sp_idx(li , 0), 0) = mac_spd(n_sp(li , 0), 0);
                    }   
                }

                MatrixXd n_p(pss_p_idx.rows() , 1);

                if (pss_p_idx.rows() != 0) {
                    for(int li = 0; li < pss_p_idx.rows() ; ++li){
                        n_p(li , 0) = mac_int((int)pss_con((int)pss_p_idx(li , 0), 0) , 1);
                        pss1(pss_p_idx(li , 0), 0) = pelect((int)n_p(li , 0), 0) * basmva / mac_con((int)n_p(li , 0), 2);
                    }   
                }
                
                if (dpw_pss_idx.rows() != 0) {
                    pss1(dpw_pss_idx, 0) = dpw_out.col(0);
                }
                pss2(pss_idx, 0) = MatrixXd::Zero(n_pss, 1);
                pss3(pss_idx, 0) = MatrixXd::Zero(n_pss, 1);
                pss_out(pss_exc_idx, 0) = MatrixXd::Zero(n_pss, 1);
                pss_pot.col(0) = pss_con.col(4).array() / pss_con.col(5).array();
                if (pss_T4_idx.size() != 0) {
                    pss_pot(pss_T4_idx, 1) = pss_con(pss_T4_idx, 6).array() / pss_T4(pss_T4_idx).array();
                }
            }
        }
    }
}