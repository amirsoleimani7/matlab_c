#include "H_header.h"

using namespace Eigen;
using namespace std;


int chq_lim(MatrixXd& bus,MatrixXd& Qg, MatrixXd& Ql,MatrixXd& qg_max ,MatrixXd& qg_min) 
{
    cout << "\n---in chq_lim---\n";
    int lim_flag = 0;    
    
    for(int i = 0 ;i <bus.rows();++i){
        if( bus(i ,9)== 2){
            if(Qg(i ,0) > qg_max(i ,0)){
                cout << "bus num is : " << bus(i ,0) << "\n"; 
                Ql(i ,0) = Ql(i ,0) - qg_max( i ,0);
                // qg_max_index(i) = 1;
                bus(i ,9) = 3;
                Qg(i ,0) = 0;
                lim_flag = 1;
            }
            if(Qg(i ,0) < qg_min(i ,0)){
                cout << "bus num is1 : " << bus(i ,0) << "\n"; 
                Ql(i ,0) = Ql(i ,0) - qg_min(i ,0);
                // qg_min_index(i) = 1;
                Qg(i ,0) = 0;
                bus(i ,9) = 3;
                lim_flag = 1;
            }
        }
    }

    cout << "\n---out chq_lim---\n";
    return lim_flag;
}
