#include "../include/H_header.h"

using namespace Eigen;
using namespace std;

void Tg_idx(MatrixXd& tg_con, MatrixXd& tg_idx, int& n_tg, MatrixXd& tgh_idx, int& n_tgh) {

    tg_idx.resize(0 ,1);
    tgh_idx.resize(0 ,1);

    if (tg_con.size() != 0) {

        for (int i = 0; i < tg_con.rows(); ++i) {
            if (tg_con(i, 0) == 1) { // how many are equal to temp            
                tg_idx.conservativeResize(tg_idx.rows() +1 , NoChange);
                tg_idx(tg_idx.rows() -1  , 0) = i + 1;
            }
            if (tg_con(i, 0) == 2) { // how many are equal to temp            
                tgh_idx.conservativeResize(tgh_idx.rows() +1 , NoChange);
                tgh_idx(tgh_idx.rows() -1  , 0) = i + 1;
            
            }
        }

    }
        
    // cout << "tg_idx is : \n" << tg_idx << "\n";
    // cout << "tg_idx size is : " << tg_idx.rows() << " " << tg_idx.cols() << "\n ";   

    n_tg = tg_idx.rows(); 
    n_tgh = tgh_idx.rows();

    // cout << "n_tg is : " << n_tg << "\n"; 
    // cout << "n_tgh is : " << n_tgh << "\n";
    // cout << "tg_idx is : \n" << tg_idx << "\n";
    // cout << "tgh_idx is : \n" << tgh_idx <<  "\n";
}
