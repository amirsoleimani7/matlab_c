#include "H_header.h"

using namespace Eigen;
using namespace std;

void pss_indx(MatrixXd& pss_con, MatrixXd& mac_con, MatrixXd& exc_con, 
              MatrixXd& pss_idx, int& n_pss, MatrixXd& pss_sp_idx, 
              MatrixXd& pss_p_idx, MatrixXd& pss_mb_idx, MatrixXd& pss_exc_idx, 
              MatrixXd& pss_T, MatrixXd& pss_T2, MatrixXd& pss_T4, 
              MatrixXd& pss_T4_idx, MatrixXd& pss_noT4) {
    
    
    if (pss_con.size() > 0) {
        int count = 0;
        for (int i = 0; i < pss_con.rows(); ++i) {
            if (pss_con(i, 0) == 1 || pss_con(i, 0) == 2) {
                count++;
            }
        }

        pss_idx.resize(count, 1);
        int idx = 0;
        for (int i = 0; i < pss_con.rows(); ++i) {
            if (pss_con(i, 0) == 1 || pss_con(i, 0) == 2) {
                pss_idx(idx, 0) = i;
                idx++;
            }
        }
        
        n_pss = pss_idx.rows();
        
        pss_mb_idx.resize(n_pss, 1);

        pss_exc_idx.resize(n_pss, 1);
        
        for (int jpss = 0; jpss < n_pss; ++jpss) {
            
            pss_mb_idx(jpss, 0) = round(pss_con((int)pss_idx(jpss, 0), 1)) - 1; // Convert to zero-based index //no need for pss_con i think  ... 
            bool found = false;

            for (int k = 0; k < exc_con.rows(); ++k) {
                if (round(pss_con((int)pss_idx(jpss, 0), 1)) == round(exc_con(k, 1))) {
                    pss_exc_idx(jpss, 0) = k;
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "You must have an exciter at the same generator as a pss\n ";            
            }
        }

        
        if (n_pss != 0) {

            pss_T.resize(n_pss, 1);
            pss_T2.resize(n_pss, 1);
            pss_T4.resize(n_pss, 1);

            int count_T4 = 0, count_noT4 = 0, count_sp = 0, count_p = 0;
            
            for (int j = 0; j < n_pss; ++j) {
            
                pss_T(j, 0) = pss_con((int)pss_idx(j, 0), 3); // generatorNo
                pss_T2(j, 0) = pss_con((int)pss_idx(j, 0), 5); // Twasshot 
                pss_T4(j, 0) = pss_con((int)pss_idx(j, 0), 7); // Tclag2

                if (pss_T4(j, 0) > 0.001) {
                    count_T4++;
                } else {
                    count_noT4++;
                }
                
                if (pss_con((int)pss_idx(j, 0), 0) == 1) {
                    count_sp++;
                } else if (pss_con((int)pss_idx(j, 0), 0) == 2) {
                    count_p++;
                }

            }
            
            pss_T4_idx.resize(count_T4, 1);
            pss_noT4.resize(count_noT4, 1);
            pss_sp_idx.resize(count_sp, 1);
            pss_p_idx.resize(count_p, 1);
            
            int idx_T4 = 0, idx_noT4 = 0, idx_sp = 0, idx_p = 0;
            
            for (int j = 0; j < n_pss; ++j) {
                if (pss_T4(j, 0) > 0.001) {
                    pss_T4_idx(idx_T4, 0) = j;
                    idx_T4++;
                } else {
                    pss_noT4(idx_noT4, 0) = j;
                    idx_noT4++;
                }

                if (pss_con((int)pss_idx(j, 0), 0) == 1) {
                    pss_sp_idx(idx_sp, 0) = j;
                    idx_sp++;

                } else if (pss_con((int)pss_idx(j, 0), 0) == 2) {
                    pss_p_idx(idx_p, 0) = j;
                    idx_p++;
                }
            }
        }

    } 
    else {
        n_pss = 0;
    }
}
