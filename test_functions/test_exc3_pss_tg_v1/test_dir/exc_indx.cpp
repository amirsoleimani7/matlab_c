#include "H_header.h"

using namespace Eigen;
using namespace std;

void exc_indx(MatrixXd& exc_con, MatrixXd& exc_pot, int& n_exc, 
              MatrixXd& st3_idx, int& n_st3,
              MatrixXd& st3_TA, MatrixXd& st3_TA_idx, MatrixXd& st3_noTA_idx,
              MatrixXd& st3_TB, MatrixXd& st3_TB_idx, MatrixXd& st3_noTB_idx,
              MatrixXd& st3_TR, MatrixXd& st3_TR_idx, MatrixXd& st3_noTR_idx) {
    
    n_st3 = 0; n_exc = 0;

    if (exc_con.size() != 0) {
        // Check for type 3 exciter
        int count_st3 = 0;
        for (int i = 0; i < exc_con.rows(); ++i) {
            if (exc_con(i, 0) == 3) {
                count_st3++;
            }
        }
       
        st3_idx.resize(count_st3, 1);
        int idx_st3 = 0;
        for (int i = 0; i < exc_con.rows(); ++i) {
            if (exc_con(i, 0) == 3) {
                st3_idx(idx_st3, 0) = i;
                idx_st3++;
            }
        }
    
        n_st3 = st3_idx.rows();
        if (n_st3 > 0) {
    // Count the number of elements that satisfy the conditions for TA, TB, and TR
    int count_TA = 0, count_noTA = 0;
    int count_TB = 0, count_noTB = 0;
    int count_TR = 0, count_noTR = 0;

    for (int i = 0; i < n_st3; ++i) {
        if (exc_con((int)st3_idx(i, 0), 4) >= 0.001) {
            count_TA++;
        } else {
            count_noTA++;
        }

        if (exc_con((int)st3_idx(i, 0), 5) >= 0.001) {
            count_TB++;
        } else {
            count_noTB++;
        }

        if (exc_con((int)st3_idx(i, 0), 2) >= 0.001) {
            count_TR++;
        } else {
            count_noTR++;
        }
    }

    st3_TA_idx.resize(count_TA, 1);
    st3_noTA_idx.resize(count_noTA, 1);
    st3_TB_idx.resize(count_TB, 1);
    st3_noTB_idx.resize(count_noTB, 1);
    st3_TR_idx.resize(count_TR, 1);
    st3_noTR_idx.resize(count_noTR, 1);

    int idx_TA = 0, idx_noTA = 0;
    int idx_TB = 0, idx_noTB = 0;
    int idx_TR = 0, idx_noTR = 0;

    for (int i = 0; i < n_st3; ++i) {
        st3_TA(i, 0) = exc_con((int)st3_idx(i, 0), 4);
        if (st3_TA(i, 0) >= 0.001) {
            st3_TA_idx(idx_TA, 0) = i;
            idx_TA++;
        } else {
            st3_noTA_idx(idx_noTA, 0) = i;
            idx_noTA++;
        }

        st3_TB(i, 0) = exc_con((int)st3_idx(i, 0), 5);
        if (st3_TB(i, 0) >= 0.001) {
            st3_TB_idx(idx_TB, 0) = i;
            idx_TB++;
        } else {
            st3_noTB_idx(idx_noTB, 0) = i;
            idx_noTB++;
        }

        st3_TR(i, 0) = exc_con((int)st3_idx(i, 0), 2);
        if (st3_TR(i, 0) >= 0.001) {
            st3_TR_idx(idx_TR, 0) = i;
            idx_TR++;
        } else {
            st3_noTR_idx(idx_noTR, 0) = i;
            idx_noTR++;
        }
    }
}


        exc_pot.resize(n_exc, 5);
        exc_pot.setZero();
    }
}
