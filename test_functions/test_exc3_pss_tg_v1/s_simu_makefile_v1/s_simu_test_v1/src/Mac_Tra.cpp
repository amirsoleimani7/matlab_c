#include "../include/H_header.h"

using namespace std;
using namespace Eigen;

void mac_tra(
    MatrixXd &bus, MatrixXd &mac_con, MatrixXd &bus_int, MatrixXd &mac_tra_idx,
    int &i, int &k, double &flag, int &n_tra, double &basmva,
    MatrixXd &mac_pot,
    MatrixXd &cur_re, MatrixXd &cur_im, 
    MatrixXd &psidpp, MatrixXd &psikd, MatrixXd &psikq, MatrixXd &psiqpp,
    MatrixXd &psi_re, MatrixXd &psi_im,
    MatrixXd &mac_ang, MatrixXd &mac_spd, MatrixXd &eqprime, MatrixXd &edprime,
    MatrixXd &curd, MatrixXd &curq, MatrixXd &curdg, MatrixXd &curqg, MatrixXd &fld_cur,
    MatrixXd &vex, MatrixXd &eterm, MatrixXd &theta, MatrixXd &ed, MatrixXd &eq,
    MatrixXd &pmech, MatrixXd &pelect, MatrixXd &qelect,
    MatrixXd &dmac_ang, MatrixXd &dmac_spd, MatrixXd &deqprime, MatrixXd &dedprime,
    MatrixXd &mcurmag,
    MatrixXd &busnum, MatrixXd &phi, MatrixXd &eqra, MatrixXd &E_Isat, MatrixXd &edra,
    MatrixXcd &curr, MatrixXcd &V, MatrixXcd &ei, MatrixXcd &rot, MatrixXcd &eprime
)
{
    cout << "we are in mac_tra\n";

    MatrixXd b = MatrixXd::Zero(4, 3); // dont need all the items tho .. 

    MatrixXd sat(3, 3);
    sat <<  0.64, 0.8, 1,
            1,    1,   1,
            1.44, 1.2, 1;

    MatrixXd inv_sat = sat.inverse();

    std::complex<double> jay(0, 1);

    for (int li = 0; li < n_tra; ++li) {
        // NOTE: This local "i" shadows the function parameter "i" (as in the original code).
        int i = mac_tra_idx(li, 0) - 1;
        busnum(i, 0) = mac_con(i, 1) - 1;

        if (mac_con(i, 13) == 0.0) {
            mac_con(i, 13) = 999.0;
        }

        mac_pot(i, 0) = basmva / mac_con(i, 2);
        mac_pot(i, 1) = 1.0;

        eterm(i, 0) = bus((int)busnum(i, 0), 1); // Terminal voltage from bus data
        theta(i, 0) = bus((int)busnum(i, 0), 2) * M_PI / 180.0;

        pelect(i, 0) = bus((int)busnum(i, 0), 3) * mac_con(i, 21);  // Pg
        qelect(i, 0) = bus((int)busnum(i, 0), 4) * mac_con(i, 22);  // Qg

        curr(i) = sqrt((pelect(i, 0) * pelect(i, 0)) + (qelect(i, 0) * qelect(i, 0))) / eterm(i, 0);
        curr(i) = curr(i) * mac_pot(i, 0);

        phi(i) = atan(qelect(i, 0) / pelect(i, 0));

        V(i) = eterm(i, 0);
        V(i) = V(i) * exp(theta(i, 0) * jay);

        curr(i) = curr(i) * exp((theta(i, 0) - phi(i, 0)) * jay);

        eprime(i, 0) = V(i, 0) + (mac_con(i, 4) + jay * mac_con(i, 6)) * curr(i, 0);
        ei(i) = V(i) + mac_con(i, 4) + jay * mac_con(i, 10) * curr(i, 0);

        mac_ang(i) = atan(ei(i).imag() / ei(i).real());
        mac_spd(i) = 1.0;

        rot(i) = exp(-jay * mac_ang(i, 0)) * jay;

        psi_re(i) = eprime(i).real();
        psi_im(i) = eprime(i).imag();

        eprime(i) = eprime(i) * rot(i);

        edprime(i) = eprime(i).real();
        eqprime(i) = eprime(i).imag();

        curr(i) = rot(i) * curr(i);
        mcurmag(i) = abs(curr(i));
        pmech(i) = pelect(i, 0) * mac_pot(i, 0) + mac_con(i, 4) * (mcurmag(i) * mcurmag(i));

        curdg(i) = curr(i).real();
        curqg(i) = curr(i).imag();

        curd(i) = curdg(i) / mac_pot(i, 0);
        curq(i) = curqg(i) / mac_pot(i, 0);

        V(i) = rot(i) * V(i);

        ed(i) = V(i).real();
        eq(i) = V(i).imag();

        MatrixXd col_1 = inv_sat.row(0).transpose();
        MatrixXd col_2 = inv_sat.row(1).transpose();
        MatrixXd col_3 = inv_sat.row(2).transpose();

        b(i, 0) = 0.8;
        b(i, 1) = 1 + mac_con(i, 19);
        b(i, 2) = 1.2 * (1 + mac_con(i, 20));

        mac_pot(i, 2) = (b.row(i) * col_1).value(); // Dot product with first column
        mac_pot(i, 3) = (b.row(i) * col_2).value(); // Dot product with second column
        mac_pot(i, 4) = (b.row(i) * col_3).value(); // Dot product with third column

        E_Isat(i, 0) = (mac_pot(i, 2) * eqprime(i, 0) * eqprime(i, 0))
                       + eqprime(i, 0) * mac_pot(i, 3)
                       + mac_pot(i, 4);

        if (eqprime(i, 0) < 0.8) {
            E_Isat(i, 0) = eqprime(i, 0);
        }

        vex(i, 0) = E_Isat(i, 0) + (mac_con(i, 5) - mac_con(i, 6)) * curdg(i, 0);

        fld_cur(i, 0) = vex(i, 0);
    }
}


