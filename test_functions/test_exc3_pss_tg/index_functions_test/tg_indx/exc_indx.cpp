#include "H_header.h"

using namespace Eigen;
using namespace std;

int smp_idx_finder(MatrixXd& exc_con){
    int smp_idx = 0;
    for (int i = 0 ; i < exc_con.rows() ;++i){
        if(exc_con(i , 0) == 0){
            smp_idx++;
        }
    }
    return smp_idx;
}

int smppi_idx_finder(MatrixXd& exc_con){
    int smppi_idx = 0;
    for (int i = 0 ; i < exc_con.rows() ;++i){
        if(exc_con(i , 0) == 4){
            smppi_idx++;
        }
    }
    return smppi_idx;
}

int dc_idx_finder(MatrixXd& exc_con){
    int dc_idx = 0;
    for (int i = 0 ; i < exc_con.rows() ;++i){
        if((exc_con(i , 0) == 1) | (exc_con(i ,4) == 2)){
            dc_idx++;
        }
    }
    return dc_idx;
}


int dcN_finder(int type , MatrixXd& exc_con){ // type can be 1 ,2 ,3 
    int dc_n = 0;
    for(int i = 0 ; i < exc_con.rows() ;++i){
        if(exc_con(i ,0) == type){
            dc_n++;
        }
    }
    return dc_n;
}

void exc_indx(MatrixXd& exc_con, MatrixXd& exc_pot, int& n_exc, 
              MatrixXd& st3_idx, int& n_st3,
              MatrixXd& st3_TA, MatrixXd& st3_TA_idx, MatrixXd& st3_noTA_idx,
              MatrixXd& st3_TB, MatrixXd& st3_TB_idx, MatrixXd& st3_noTB_idx,
              MatrixXd& st3_TR, MatrixXd& st3_TR_idx, MatrixXd& st3_noTR_idx) {
    
    n_st3 = 0; n_exc = 0;
    
    int n_smp = smp_idx_finder(exc_con);
    MatrixXd smp_idx(n_smp , 1);
    
    for(int i = 0 ; i <n_smp ;++i){
        if(exc_con(i , 0) == 0){
            smp_idx(i ,0) = i+1 ;
        }
    }

    int n_smppi = smppi_idx_finder(exc_con);
    MatrixXd smppi_idx(n_smppi , 1);

    for(int i = 0 ; i < n_smppi ; ++i){
        if(exc_con(i ,0) == 4){
            smppi_idx(i ,0) = i + 1;
        }
    }

    int n_dc = dc_idx_finder(exc_con);
    MatrixXd dc_idx(n_dc , 1);

    for(int i = 0 ; i < n_dc ; ++i){
        if((exc_con(i ,0) == 1) || (exc_con(i ,0) == 2)){
            dc_idx(i ,0) = i + 1;
        }
    }

    int n_dc1 = dcN_finder(1 , exc_con);
    int n_dc2 = dcN_finder(2 , exc_con);
    int n_dc3 = dcN_finder(3 , exc_con);

    MatrixXd dc1_idx(n_dc1 , 1);
    MatrixXd dc2_idx(n_dc2 , 1);
    MatrixXd dc3_idx(n_dc3 , 1);

    for(int i = 0 ; i < n_dc ; ++i){
        if((exc_con(i ,0) == 1)){
            dc1_idx(i ,0) = i + 1;
        }
    }
    
    for(int i = 0 ; i < n_dc ; ++i){
        if((exc_con(i ,0) == 2)){
            dc2_idx(i ,0) = i + 1;
        }
    }
    
    for(int i = 0 ; i < n_dc ; ++i){
        if(exc_con(i , 0) == 3){
            dc3_idx(i ,0) = i + 1;
        }
    }


    if (exc_con.size() != 0) {
        int count_st3 = 0;
        for (int i = 0; i < exc_con.rows(); ++i) {
            if (exc_con(i, 0) == 3) {
                count_st3++;
            }
        }
        

        st3_idx.resize(count_st3, 1);

        int idx_st3 = 1;
        
        for (int i = 0; i < exc_con.rows(); ++i) {
            if (exc_con(i, 0) == 3) {
                st3_idx(i, 0) = idx_st3;
                idx_st3++;
            }
        }

        
        n_st3 = st3_idx.rows(); // which is the number of count_st3

        if (n_st3 > 0) {

            int count_TA = 0, count_noTA = 0;
            int count_TB = 0, count_noTB = 0;
            int count_TR = 0, count_noTR = 0;

            for (int i = 0; i < n_st3; ++i) {
        
                if (exc_con((int)st3_idx(i, 0) -1, 4) >= 0.001) {
                    count_TA++;
                } else {
                    count_noTA++;
                }

                if (exc_con((int)st3_idx(i, 0) -1, 5) >= 0.001) {
                    count_TB++;
                } else {
                    count_noTB++;
                }

                if (exc_con((int)st3_idx(i, 0) -1, 2) >= 0.001) {
                    count_TR++;
                } else {
                    count_noTR++;
                }
            }

            st3_TA.resize(4 ,1);
            st3_TB.resize(4 ,1);
            st3_TR.resize(4 ,1);


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

                st3_TA(i, 0) = exc_con((int)st3_idx(i, 0) -1, 4);

                if (st3_TA(i, 0) >= 0.001) {
                    st3_TA_idx(idx_TA , 0) = i + 1;
                    idx_TA++;
                } else {
                    st3_noTA_idx(idx_noTA, 0) = i + 1;  
                    idx_noTA++;
                }

                st3_TB(i, 0) = exc_con((int)st3_idx(i, 0) -1, 5);
                if (st3_TB(i, 0) >= 0.001) {
                    st3_TB_idx(idx_TB, 0) = i + 1;
                    idx_TB++;
                } else {
                    st3_noTB_idx(idx_noTB, 0) = i + 1;
                    idx_noTB++;
                }

                st3_TR(i, 0) = exc_con((int)st3_idx(i, 0) -1, 2);
                if (st3_TR(i, 0) >= 0.001) {
                    st3_TR_idx(idx_TR, 0) = i +1 ;
                    idx_TR++;
                } else {
                    st3_noTR_idx(idx_noTR, 0) = i +1;
                    idx_noTR++;
                }
            }
        }

            n_exc = n_smp+n_smppi+n_dc+n_st3;
            exc_pot.resize(n_exc, 5);  // this should be set as well 
            exc_pot.setZero();

        }


    cout << "n_st3  is : " << n_st3 << "\n";
    cout << "n_exc : " << n_exc << "\n";
    cout << "n_smp is : " << n_smp <<"\n";
    cout << "n_smppi is : " << n_smppi <<"\n";
    cout << "n_dc  : " << n_dc << "\n";
    cout << "n_dc1 : " << n_dc1 << "\n";
    cout << "n_dc2 : " << n_dc2 << "\n";
    cout << "n_dc3 : " << n_dc3 << "\n";




    cout << "exc_con : \n" << exc_con << "\n";
    cout << "exc_pot : \n" << exc_pot << "\n";
    cout << "n_exc : \n" << n_exc << "\n";
    cout << "st3_idx : \n" << st3_idx << "\n";
    cout << "n_st3 : \n" << n_st3 << "\n";

    cout << "st3_TA : \n" << st3_TA << "\n";
    cout << "st3_TA_idx : \n" << st3_TA_idx << "\n";
    cout << "st3_noTA_idx : \n" << st3_noTA_idx << "\n";

    cout << "st3_TB : \n" << st3_TB << "\n";
    cout << "st3_TB_idx : \n" << st3_TB_idx << "\n";
    cout << "st3_noTB_idx : \n" << st3_noTB_idx << "\n";


    cout << "st3_TR : \n" << st3_TR << "\n";
    cout << "st3_TR_idx : \n" << st3_TR_idx << "\n";
    cout << "st3_noTR_idx : \n" << st3_noTR_idx << "\n";


}
