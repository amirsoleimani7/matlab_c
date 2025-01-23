#include "H_header.h"

using namespace Eigen;
using namespace std;

void gov_indx(MatrixXd& tg_con, MatrixXd& tg_idx, int& n_tg, MatrixXd& tgh_idx, int& n_tgh) {

    n_tg = 0;
    n_tgh = 0;

    if (tg_con.size() != 0) {

        int count_tg = 0;
    
        for (int i = 0; i < tg_con.rows(); ++i) {
            if (tg_con(i, 0) == 1) { // how many are equal to temp
                count_tg++;
            }
        }

        tg_idx.resize(count_tg, 1);
        
        int idx_tg = 0;

        for (int i = 0; i < tg_con.rows(); ++i) {
            if (tg_con(i, 0) == 1) {
                tg_idx(idx_tg, 0) = i;
                idx_tg++;
            }
        }

        n_tg = tg_idx.rows(); // length(tg_idx)
        
        // Find indices where tg_con(:,1) == 2
        
        int count_tgh = 0;
        for (int i = 0; i < tg_con.rows(); ++i) {
            if (tg_con(i, 0) == 2) {
                count_tgh++;
            }
        }

        tgh_idx.resize(count_tgh, 1);
        int idx_tgh = 0;
        for (int i = 0; i < tg_con.rows(); ++i) {
            if (tg_con(i, 0) == 2) {
                tgh_idx(idx_tgh, 0) = i;
                idx_tgh++;
            }
        }

        n_tgh = tgh_idx.rows();
    }
}
