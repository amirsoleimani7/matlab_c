#include "H_header.h"

using namespace std;
using namespace Eigen;


// MatrixXd mac_pot, mac_con, ind_con, igen_con, ibus_con;
// MatrixXd mac_int, ind_int, igen_int, mac_em_idx, mac_tra_idx, mac_sub_idx, mac_ib_idx, not_ib_idx;
int n_mac, n_em, ngm, n_tot, n_tra, n_sub, n_ib, n_ib_em, n_ib_tra, n_ib_sub, n_mot, n_ig , n_par;

void mac_indx(MatrixXd& mac_con, MatrixXd& mac_pot, MatrixXd& mac_em_idx, 
              MatrixXd& mac_tra_idx, MatrixXd& mac_sub_idx, MatrixXd& mac_int, 
              int& macmax, int& n_mac, int& n_tot, int& n_ig, int& n_em, 
              int& n_tra, int& n_sub , MatrixXd &not_ib_idx , int &ngm){

    n_mac = mac_con.rows();
    mac_pot = MatrixXd::Zero(n_mac, 15); // making mac_pot all zero 

    macmax = mac_con.col(0).maxCoeff(); 
    
    // if (n_par < 22) { //(adding 4 columns and setting the last two on 1's)this is already done on the data
    //     mac_con.conservativeResize(mac_con.rows(), std::max(23, static_cast<int>(mac_con.cols())));
    //     mac_con.block(0, 21, mac_con.rows(), 2).setOnes(); // Set columns 22 and 23 to ones (0-based index: 21, 22)
    // }

    mac_int = MatrixXd::Zero(macmax, 1);  


    for (int i = 0; i < n_mac; ++i) { // the rest of the cells should zero
        mac_int(int(mac_con(i, 0)) - 1, 0) = i + 1;
    }

    not_ib_idx.resize(n_mac ,1);
    for (int i = 0; i < n_mac; ++i) { // the rest of the cells should zero
        not_ib_idx(i ,0) = i+1;
    }
    
    n_tot = n_mac;
    ngm = n_mac;
    n_mot = 0;
    n_ig = 0;
    
    n_ib = 0;
    n_ib_em = 0;
    n_ib_tra = 0;
    n_ib_sub = 0;

    mac_em_idx.resize(0, 1);
    mac_tra_idx.resize(0, 1);
    mac_sub_idx.resize(0, 1);

    for(int i = 0 ; i < n_mac ; i++){
        if(mac_con(i , 5) == 0){
            mac_em_idx.conservativeResize(mac_em_idx.rows() + 1, Eigen::NoChange);
            mac_em_idx(mac_em_idx.rows() -1 , 0) =  i + 1; 
        }
        else{   
            if(mac_con(i , 7) == 0){
                mac_tra_idx.conservativeResize(mac_tra_idx.rows() +1 , Eigen::NoChange);
                mac_tra_idx(mac_tra_idx.rows() -1 , 0) = i + 1;
            }
            else{
                mac_sub_idx.conservativeResize(mac_sub_idx.rows() +1 , Eigen::NoChange);
                mac_sub_idx(mac_sub_idx.rows() -1  , 0)= i + 1;
            }
        }
    }



    n_em = mac_em_idx.rows();
    n_tra = mac_tra_idx.rows();
    n_sub = mac_sub_idx.rows();
    
    // cout << "mac_em_idx is :\n" << mac_em_idx <<"\n";
    // cout << "mac_tra_idx is : \n" << mac_tra_idx <<"\n";
    // cout << "mac_sub_idx is  : \n" << mac_sub_idx <<"\n";
    // cout << "mac_int is : \n " << mac_int <<"\n";


    // cout << "macmax is : " << macmax << "\n";
    // cout << "n_mac is : " << n_mac <<"\n";
    // cout << "n_tot is : " << n_tot << "\n";
    // cout << "n_ig is : " << n_ig << "\n";
    // cout << "n_em is : " << n_em <<"\n";
    // cout << "n_tra is : " << n_tra <<"\n";
    // cout << "n_sub is : " << n_sub <<"\n";


}
