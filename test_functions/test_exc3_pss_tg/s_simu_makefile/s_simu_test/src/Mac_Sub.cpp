#include "../include/H_header.h"

using namespace std;
using namespace Eigen;

// Revised function prototype with all computed matrices passed as reference output parameters

void mac_sub(
    int i,            // (Unused; originally "i")
    int flag,
    const MatrixXd &bus,
    MatrixXd &mac_con,
    const MatrixXd &bus_int,
    const MatrixXd &mac_sub_idx,
    double n_sub,         // number of subtransient machines
    double basmva,
    MatrixXd &mac_pot,
    MatrixXd &cur_re,
    MatrixXd &cur_im,
    MatrixXd &psidpp,
    MatrixXd &psikd,
    MatrixXd &psikq,
    MatrixXd &psiqpp,
    MatrixXd &psi_re,
    MatrixXd &psi_im,
    MatrixXd &mac_ang,
    MatrixXd &mac_spd,
    MatrixXd &eqprime,
    MatrixXd &edprime,
    MatrixXd &curd,
    MatrixXd &curq,
    MatrixXd &curdg,
    MatrixXd &curqg,
    MatrixXd &fld_cur,
    MatrixXd &vex,
    MatrixXd &eterm,
    MatrixXd &theta,
    MatrixXd &ed,
    MatrixXd &eq,
    MatrixXd &pmech,
    MatrixXd &pelect,
    MatrixXd &qelect,
    MatrixXd &dmac_ang,
    MatrixXd &dmac_spd,
    MatrixXd &deqprime,
    MatrixXd &dedprime,
    MatrixXd &mcurmag,
    MatrixXd &busnum,
    MatrixXd &phi,
    MatrixXd &eqra,
    MatrixXd &E_Isat,
    MatrixXd &edra,
    MatrixXcd &curr,
    MatrixXcd &V,
    MatrixXcd &ei,
    MatrixXcd &rot
)
{
    cout << "we are in the mac_sub\n";
    const std::complex<double> jay(0, 1); 

    int n = 4 ; // total numebr of machines ...  
    mac_pot = MatrixXd::Zero(n, 23);
    cur_re   = MatrixXd::Zero(n, 1);
    cur_im   = MatrixXd::Zero(n, 1);
    psidpp   = MatrixXd::Zero(n, 1);
    psikd    = MatrixXd::Zero(n, 1);
    psikq    = MatrixXd::Zero(n, 1);
    psiqpp   = MatrixXd::Zero(n, 1);
    psi_re   = MatrixXd::Zero(n, 1);
    psi_im   = MatrixXd::Zero(n, 1);
    mac_ang  = MatrixXd::Zero(n, 1);
    mac_spd  = MatrixXd::Zero(n, 1);
    eqprime  = MatrixXd::Zero(n, 1);
    edprime  = MatrixXd::Zero(n, 1);
    curd     = MatrixXd::Zero(n, 1);
    curq     = MatrixXd::Zero(n, 1);
    curdg    = MatrixXd::Zero(n, 1);
    curqg    = MatrixXd::Zero(n, 1);
    fld_cur  = MatrixXd::Zero(n, 1);
    vex      = MatrixXd::Zero(n, 1);
    eterm    = MatrixXd::Zero(n, 1);
    theta    = MatrixXd::Zero(n, 1);
    ed       = MatrixXd::Zero(n, 1);
    eq       = MatrixXd::Zero(n, 1);
    pmech    = MatrixXd::Zero(n, 1);
    pelect   = MatrixXd::Zero(n, 1);
    qelect   = MatrixXd::Zero(n, 1);
    dmac_ang = MatrixXd::Zero(n, 1);
    dmac_spd = MatrixXd::Zero(n, 1);
    deqprime = MatrixXd::Zero(n, 1);
    dedprime = MatrixXd::Zero(n, 1);
    mcurmag  = MatrixXd::Zero(n, 1);
    busnum   = MatrixXd::Zero(n, 1);
    phi      = MatrixXd::Zero(n, 1);
    eqra     = MatrixXd::Zero(n, 1);
    E_Isat   = MatrixXd::Zero(n, 1);
    edra     = MatrixXd::Zero(n, 1);
    curr     = MatrixXcd::Zero(n, 1);  // if curr is a complex matrix
    V        = MatrixXcd::Zero(n, 1);   // if V is a complex matrix
    ei       = MatrixXcd::Zero(n, 1);   // if ei is a complex matrix
    rot      = MatrixXcd::Zero(n, 1);   // if rot is a complex matrix
    
    MatrixXd b = MatrixXd::Zero(n, 3);

    MatrixXd sat(3, 3);
    sat << 0.64, 0.8, 1,
           1,    1,   1,
           1.44, 1.2, 1;

    MatrixXd inv_sat = sat.inverse();

    for (int li = 0; li < n_sub; ++li) { // the loop is on the n_** but the sizes are the same
        // Avoid conflict with the function parameter "dummy" by using "idx" for the machine index
        int idx = mac_sub_idx(li, 0) - 1;
    
        busnum(idx, 0) = mac_con(idx, 1) - 1;
        
        // Update mac_con values if necessary
        if (mac_con(idx, 7) != mac_con(idx, 12))
            mac_con(idx, 12) = mac_con(idx, 7);
        if (mac_con(idx, 13) == 0.0)
            mac_con(idx, 13) = 999.0;
        if (mac_con(idx, 14) == 0)
            mac_con(idx, 14) = 999.0;

        mac_pot(idx, 0) = basmva / mac_con(idx, 2);
        mac_pot(idx, 1) = 1.0;
        mac_pot(idx, 7) = mac_con(idx, 6) - mac_con(idx, 3);
        mac_pot(idx, 8) = (mac_con(idx, 7) - mac_con(idx, 3)) / mac_pot(idx, 7);
        mac_pot(idx, 6) = (mac_con(idx, 5) - mac_con(idx, 6)) * mac_pot(idx, 8);
        mac_pot(idx, 9) = (mac_con(idx, 6) - mac_con(idx, 7)) / mac_pot(idx, 7);
        mac_pot(idx, 5) = (mac_con(idx, 5) - mac_con(idx, 6)) / mac_pot(idx, 7) * mac_pot(idx, 9);
        mac_pot(idx, 12) = mac_con(idx, 11) - mac_con(idx, 3);
        mac_pot(idx, 13) = (mac_con(idx, 12) - mac_con(idx, 3)) / mac_pot(idx, 12);
        mac_pot(idx, 11) = (mac_con(idx, 10) - mac_con(idx, 11)) * mac_pot(idx, 13);
        mac_pot(idx, 14) = (mac_con(idx, 11) - mac_con(idx, 12)) / mac_pot(idx, 12);
        mac_pot(idx, 10) = (mac_con(idx, 10) - mac_con(idx, 11)) / mac_pot(idx, 12) * mac_pot(idx, 14);

        // Get terminal voltage and angle from bus data
        eterm(idx, 0) = bus((int)busnum(idx, 0), 1);
        theta(idx, 0) = bus((int)busnum(idx, 0), 2) * M_PI / 180.0;

        // Compute electrical power values (Pg and Qg)
        
        pelect(idx, 0) = bus((int)busnum(idx, 0), 3) * mac_con(idx, 21);
        qelect(idx, 0) = bus((int)busnum(idx, 0), 4) * mac_con(idx, 22);

        // Compute current magnitude and adjust with machine potential
        curr(idx) = sqrt(pow(pelect(idx, 0), 2) + pow(qelect(idx, 0), 2)) / eterm(idx, 0);
        curr(idx) = curr(idx) * mac_pot(idx, 0);

        // Compute load angle
        phi(idx) = atan(qelect(idx, 0) / pelect(idx, 0));

        // Build the complex voltage V and current (curr)
        V(idx) = eterm(idx, 0);
        V(idx) = V(idx) * exp(theta(idx, 0) * jay);
        curr(idx) = curr(idx) * exp((theta(idx, 0) - phi(idx, 0)) * jay);

        // Calculate internal voltage (ei)
        ei(idx) = V(idx) + mac_con(idx, 4) + jay * mac_con(idx, 10) * curr(idx, 0);
        mac_ang(idx) = atan(ei(idx).imag() / ei(idx).real());
        mac_spd(idx) = 1.0;

        // Compute rotation and update current
        rot(idx) = exp(-jay * mac_ang(idx, 0)) * jay;
        curr(idx) = rot(idx) * curr(idx);

        // Compute current components
        curdg(idx) = curr(idx).real();
        curqg(idx) = curr(idx).imag();
        curd(idx) = curdg(idx) / mac_pot(idx, 0);
        curq(idx) = curqg(idx) / mac_pot(idx, 0);
        mcurmag(idx) = abs(curr(idx));

        // Mechanical power calculation
        pmech(idx) = pelect(idx, 0) * mac_pot(idx, 0) + mac_con(idx, 4) * (mcurmag(idx) * mcurmag(idx));

        // Rotate voltage for further calculations
        V(idx) = rot(idx) * V(idx);
        ed(idx) = V(idx).real();
        eq(idx) = V(idx).imag();

        eqra(idx) = eq(idx, 0) + mac_con(idx, 4) * curqg(idx, 0);
        psidpp(idx) = eqra(idx) + mac_con(idx, 7) * curdg(idx, 0);
        psikd(idx, 0) = eqra(idx) + mac_con(idx, 3) * curdg(idx, 0);
        eqprime(idx, 0) = eqra(idx) + mac_con(idx, 6) * curdg(idx, 0);
        edra(idx, 0) = -ed(idx, 0) - mac_con(idx, 4) * curdg(idx, 0);
        psiqpp(idx, 0) = edra(idx, 0) + mac_con(idx, 12) * curqg(idx, 0);
        psikq(idx, 0) = edra(idx, 0) + mac_con(idx, 3) * curqg(idx, 0);
        edprime(idx, 0) = edra(idx, 0) + mac_con(idx, 11) * curqg(idx, 0);

        // Use the inverse saturation matrix to compute additional machine parameters
        MatrixXd col_1 = inv_sat.row(0).transpose();
        MatrixXd col_2 = inv_sat.row(1).transpose();
        MatrixXd col_3 = inv_sat.row(2).transpose();
        b(idx, 0) = 0.8;
        b(idx, 1) = 1 + mac_con(idx, 19);
        b(idx, 2) = 1.2 * (1 + mac_con(idx, 20));
        mac_pot(idx, 2) = (b.row(idx) * col_1).value();
        mac_pot(idx, 3) = (b.row(idx) * col_2).value();
        mac_pot(idx, 4) = (b.row(idx) * col_3).value();

        // Compute saturation current (E_Isat)
        E_Isat(idx, 0) = (mac_pot(idx, 2) * eqprime(idx, 0) * eqprime(idx, 0))
                         + eqprime(idx, 0) * mac_pot(idx, 3)
                         + mac_pot(idx, 4);
        if (eqprime(idx, 0) < 0.8)
            E_Isat(idx, 0) = eqprime(idx, 0);

        // Calculate excitation voltage (vex) and field current
        vex(idx, 0) = E_Isat(idx, 0)
                      + mac_pot(idx, 5) * (eqprime(idx, 0) - psikd(idx, 0))
                      + mac_pot(idx, 6) * curdg(idx, 0);
        fld_cur(idx, 0) = vex(idx, 0);

        
        // Compute the real and imaginary parts of the internal flux
        psi_re(idx, 0) = (-sin(mac_ang(idx, 0)) * psiqpp(idx, 0)) + (cos(mac_ang(idx, 0)) * psidpp(idx, 0));
        psi_im(idx, 0) = (cos(mac_ang(idx, 0)) * psiqpp(idx, 0)) + (sin(mac_ang(idx, 0)) * psidpp(idx, 0));
    }

}

