#include "../include/H_header.h"

using namespace std;
using namespace Eigen;
 
void mac_em(
    MatrixXd bus, MatrixXd mac_con, MatrixXd bus_int, MatrixXd mac_em_idx,
    int i, int k, double flag, int  &n_em, double &basmva,
    MatrixXd &mac_pot,
    MatrixXd &eterm, MatrixXd &pelect, MatrixXd &qelect, MatrixXd &phi,
    MatrixXd &psi_re, MatrixXd &psi_im, MatrixXd &mac_ang, MatrixXd &mac_spd,
    MatrixXd &eqprime, MatrixXd &vex, MatrixXd &edprime, MatrixXd &busnum,
    MatrixXd &curqg, MatrixXd &curdg, MatrixXd &eq, MatrixXd &ed,
    MatrixXd &curq, MatrixXd &curd, MatrixXd &pmech, MatrixXd &theta,
    MatrixXcd &V, MatrixXcd &curr, MatrixXcd &eprime, MatrixXcd &ei, MatrixXcd &rot
)

{
    complex<double> jay(0.0, 1.0); 

    for (int lk = 0; lk < n_em; ++lk)
    {
        int li = mac_em_idx(lk, 0) - 1;
        
        busnum(li, 0) = mac_con(li, 1) - 1;

        mac_pot(li, 0) = basmva / mac_con(li, 2);
        mac_pot(li, 1) = 1.0;

        eterm(li, 0) = bus((int)busnum(li, 0), 1); // putting the v in there ..
        theta(li, 0) = bus((int)busnum(li, 0), 2) * M_PI / 180.0;

        pelect(li, 0) = (bus((int)busnum(li, 0), 3) * mac_con(li, 21));  // Pg
        qelect(li, 0) = (bus((int)busnum(li, 0), 4) * mac_con(li, 22));  // Qg

        curr(li) = sqrt((pelect(li, 0) * pelect(li, 0)) + (qelect(li, 0) * qelect(li, 0))) / eterm(li, 0);
        curr(li) = curr(li) * mac_pot(li, 0);

        phi(li) = atan(qelect(li, 0) / pelect(li, 0));

        V(li) = (eterm(li, 0));
        V(li) = V(li) * exp(theta(li, 0) * jay);
        
        curr(li) = curr(li) * exp((theta(li, 0) - phi(li, 0)) * jay);

        eprime(li) = V(li, 0) + (jay * mac_con(li, 6) * curr(li, 0));

        ei(li) = eprime(li);
        mac_ang(li) = atan(ei(li).imag() / ei(li).real());
        mac_spd(li) = 1.0;
        
        rot(li) = exp(-jay * mac_ang(li, 0)) * jay;

        psi_re(li) = eprime(li).real();
        psi_im(li) = eprime(li).imag();
    
        eprime(li) = rot(li) * eprime(li);

        edprime(li) = eprime(li).real();
        eqprime(li) = eprime(li).imag();

        curr(li) = rot(li) * curr(li);

        curdg(li) = curr(li).real();
        curqg(li) = curr(li).imag();

        curd(li) = curdg(li) / mac_pot(li, 0);
        curq(li) = curqg(li) / mac_pot(li, 0);

        V(li) = rot(li) * V(li);
        ed(li) = V(li).real();
        eq(li) = V(li).imag();

        vex(li) = eqprime(li, 0);

        pmech(li, 0) = (pelect(li, 0) * mac_pot(li, 0));        
    }
}
