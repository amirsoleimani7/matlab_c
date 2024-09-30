#include "H_header.h"

using namespace std;
using namespace Eigen;

// mac_em gets bus , mac_con , bus_int , mac_em_idx , other
void mac_em(MatrixXd bus ,MatrixXd mac_con ,MatrixXd bus_int ,MatrixXd mac_em_idx,
        double i ,double k , double flag ,double n_em,double basmva)
{
    
    MatrixXd mac_em_idx ,mac_pot ,mac_con ,eterm,pelect,qelect, phi
    ,psi_re , psi_im ,mac_ang ,mac_spd  ,eqprime ,vex ,edprime,busnum
    , mac_con,bus_int, curqg ,curdg ,eq , ed ,curq , curd ,pmech ,theta;
    
    MatrixXcd V ,curr , eprime , ei , rot;

    complex<double> jay(0.0 ,1.0); 

        for (int lk=0;lk < n_em;++lk)
    {
        int li = mac_em_idx(lk , 0) -1;

        mac_pot(li , 0) = basmva / mac_con(li ,2);
        
        mac_pot(li, 1) = 1.0;

        eterm(li ,0) = bus((int)busnum(li , 0) ,1); //putting the v in there ..
        
        theta(li ,0 ) = bus((int)busnum(li,0),2) * M_PI / 180.0;

        pelect(li ,0) = (bus((int)busnum(li, 0), 3) * mac_con(li , 21));  //Pg
        qelect(li ,0) = (bus((int)busnum(li, 0), 4) * mac_con(li , 22));  //Qg

        curr(li) = sqrt((pelect(li ,0) * pelect(li ,0)) + (qelect(li ,0) * qelect(li, 0))) / (mac_pot(li,0) * eterm(li ,0));

        phi(li) = atan(qelect(li ,0) / pelect(li ,0));
        
        V(li) = (eterm(li ,0));
        V(li) = V(li) *  exp(theta((int)busnum(li) ,0)  * jay);
        
        curr(li) = curr(li) * exp((theta((int)busnum(li) ,0) - phi(li, 0)) * jay);

        eprime(li) = V(li ,0) + (jay * mac_con(li ,6) * curr(li ,0));

        ei(li) = eprime(li);
        
        mac_ang(li) = atan(ei(li).imag() / ei(li).real());
        mac_spd(li) = 1.0;
        
        rot(li) = exp(complex<double>(0.0 , -1.0) * jay * mac_ang(li ,0)) * jay;

        psi_re(li) = eprime(li).real();
        psi_im(li) = eprime(li).imag();
    
        eprime(li) = rot(li) * eprime(li);

        edprime(li) = eprime(li).real();
        eqprime(li) = eprime(li).imag();

        curr(li) = rot(li) * curr(li);

        curdg(li) = curr(li).real();
        curqg(li) = curr(li).imag();
        
        curd(li) = curdg(li) /  mac_pot(li ,0);
        curq(li) = curdg(li) / mac_pot(li ,0);

        V(li) = rot(li) * V(li);
        
        ed(li) = V(li).real();
        eq(li) = V(li).imag();

        vex(li) = eqprime(li ,0);

        pmech(li , 1) = (pelect(li ,0) * mac_pot(li ,0));        
    }
    cout << "curd is \n" << curd << "\n";
    cout << "curdg is \n" << curdg << "\n";
    cout << "curq is \n" << curq << "\n";
    cout << "curqg is \n" << curqg << "\n";
    cout << "ed is \n" << ed << "\n";
    cout << "edprime is \n" << edprime << "\n";
    cout << "eq is \n" << eq << "\n";
    cout << "eqprime is \n" << eqprime << "\n";
    cout << "etern  is \n" << eterm << "\n";
    cout << "mac_ang  is \n" << mac_ang << "\n";
    cout << "mac_spd  is \n" << mac_spd << "\n";
    cout << "pelect  is \n" << pelect << "\n";
    cout << "qelect  is \n" << qelect << "\n";
    cout << "pmetch  is \n" << pmech << "\n";
    cout << "phi  is \n" << phi << "\n";
    cout << "psi_im  is \n" << psi_im  << "\n";
    cout << "psi_re  is \n" << psi_re  << "\n";
    cout << "vex  is \n" << vex   << "\n";
    cout << "rot  is \n" << rot   << "\n";
    cout << "curr  is \n" << curr  << "\n";
    cout << "ei  is \n" << ei  << "\n";
    cout << "eprime  is \n" << eprime  << "\n";
    cout << "v  is \n" << V  << "\n";
}