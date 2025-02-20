#include "../include/H_header.h"

using namespace std;
using namespace Eigen;



void nc_load(MatrixXd &bus , int falg , MatrixXd &load_con,
            MatrixXd &j  ,MatrixXcd &V_nc  , MatrixXcd &S_cc , MatrixXcd &load_pot
){

    complex<double> jay(0.0, 1.0); // sqrt(-1)
    
    int nload = load_con.col(1).rows(); // number of rows for the load_con
    
    V_nc.resize(nload , 1);
    load_pot.resize(nload , 4);
    S_cc.resize(nload , 1);
    j.resize(nload , 1);
    
    for(int li = 0 ;li < nload ;++li){
        int lj = load_con(li ,0) -1;
        j(li , 0) = lj + 1; 
        V_nc(li ,0) = bus(lj , 1) * exp(jay * bus(lj , 2) * M_PI / 180.0);
        load_pot(li , 0) = (bus(lj ,5) * load_con(li , 1)) + (jay * bus(lj ,6) * load_con(li ,2));
        S_cc(li , 0) = (bus(lj ,5) * load_con(li ,3)) + (jay * bus(lj ,6) * load_con(li ,4));
        load_pot(li , 1) = S_cc(li ,0) / abs(V_nc(li ,0));
        load_pot(li , 2) = load_pot(li ,0) / V_nc(li , 0) / conj(V_nc(li ,0));
        load_pot(li , 3) = S_cc(li ,0) / V_nc(li , 0) / conj(V_nc(li ,0));
    }

}
