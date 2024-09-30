#include "H_header.h"

using namespace std;
using namespace Eigen;


void mac_em(int i ,int k,MatrixXd bus , int flag)
{
    
    MatrixXd mac_em_idx ,mac_pot ,mac_con ,eterm,pelect,qelect, phi
    ,psi_re , psi_im ,mac_ang ,mac_spd  ,eqprime ,vex ,edprime,busnum
    , mac_con,bus_int, curqg ,curdg ,eq , ed ,curq , curd ,pmech;
    
    MatrixXcd V ,curr , eprime , ei , rot;
    double busmva; //constant given in the input ...
    int n_em; //size of the mac_em_idxt

    complex<double> jay(0.0 ,1.0);

    for (int lk=0;lk < n_em;++lk)
    {

        int li = mac_em_idx[lk];
        mac_pot(li ,1) = busmva / mac_con(li ,3);
        mac_pot(li ,2) = 1.0;
        
        busnum(li) = bus_int((int)mac_con(li,2)); //bus numbers are saved here ....
        eterm(li) = bus((int)busnum(li) ,2); //this for the V of the busnum(li)
        V(li) = (eterm(li) * exp(bus((int)busnum(li) ,3)  * jay));
        
        pelect(li) = (bus((int)busnum(li), 3) * mac_con(li , 22));  //Pg
        pelect(li) = (bus((int)busnum(li), 4) * mac_con(li , 23));  //Qg

        curr(li) = sqrt((pelect(li) * pelect(li)) + (qelect(li) * qelect(li))) / (mac_pot(li,1) * eterm(li));
        phi(li) = atan(qelect(li) / pelect(li));
        curr(li) = exp((bus((int)busnum(li) ,3) - phi(li)) * jay) * curr(li);
        eprime(li) = V(li) * jay * mac_con(li ,7) * curr(li);
        ei(li) = eprime(li);
        psi_im(li) = eprime(li).imag();
        psi_re(li) = eprime(li).real();
        mac_ang(li) = atan(ei(li).imag() / ei(li).real());
        mac_spd(li) = 1.0;
        rot(li) = exp(complex<double>(-1.0 , 0.0) * jay * mac_ang(li))* jay;
        eprime(li) = rot(li) * eprime(li);
        eqprime(li) = eprime(li).imag();
        vex(li) = eqprime(li);
        edprime(li) = eprime(li).real();

        curr(li) = rot(li) * curr(li);
        curqg(li) = curr(li).imag();
        curdg(li) = curr(li).real();

        curd(li) = curdg(li) /  mac_pot(li ,1);
        curq(li) = curdg(li) / mac_pot(li ,1);
        pmech(li , 1) = (pelect(li) * mac_pot(li ,1));

        V(li) = rot(li) * V(li);
        eq(li) = V(li).imag();
        ed(li) = V(li).real();
    }

}