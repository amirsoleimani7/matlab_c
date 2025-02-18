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
    
    int n = 4 ; // total machines  ... 
// Resize the matrices
mac_pot.resize(n, 23);
cur_re.resize(n, 1);
cur_im.resize(n, 1);
psidpp.resize(n, 1);
psikd.resize(n, 1);
psikq.resize(n, 1);
psiqpp.resize(n, 1);
psi_re.resize(n, 1);
psi_im.resize(n, 1);
mac_ang.resize(n, 1);
mac_spd.resize(n, 1);
eqprime.resize(n, 1);
edprime.resize(n, 1);
curd.resize(n, 1);
curq.resize(n, 1);
curdg.resize(n, 1);
curqg.resize(n, 1);
fld_cur.resize(n, 1);
vex.resize(n, 1);
eterm.resize(n, 1);
theta.resize(n, 1);
ed.resize(n, 1);
eq.resize(n, 1);
pmech.resize(n, 1);
pelect.resize(n, 1);
qelect.resize(n, 1);
dmac_ang.resize(n, 1);
dmac_spd.resize(n, 1);
deqprime.resize(n, 1);
dedprime.resize(n, 1);
mcurmag.resize(n, 1);
busnum.resize(n, 1);
phi.resize(n, 1);
eqra.resize(n, 1);
E_Isat.resize(n, 1);
edra.resize(n, 1);
curr.resize(n, 1);
V.resize(n, 1);
ei.resize(n, 1);
rot.resize(n, 1);

// Initialize them to zero
mac_pot.setZero();
cur_re.setZero();
cur_im.setZero();
psidpp.setZero();
psikd.setZero();
psikq.setZero();
psiqpp.setZero();
psi_re.setZero();
psi_im.setZero();
mac_ang.setZero();
mac_spd.setZero();
eqprime.setZero();
edprime.setZero();
curd.setZero();
curq.setZero();
curdg.setZero();
curqg.setZero();
fld_cur.setZero();
vex.setZero();
eterm.setZero();
theta.setZero();
ed.setZero();
eq.setZero();
pmech.setZero();
pelect.setZero();
qelect.setZero();
dmac_ang.setZero();
dmac_spd.setZero();
deqprime.setZero();
dedprime.setZero();
mcurmag.setZero();
busnum.setZero();
phi.setZero();
eqra.setZero();
E_Isat.setZero();
edra.setZero();
curr.setZero();
V.setZero();
ei.setZero();
rot.setZero();


    // Local intermediate matrix b (n x 3)
    MatrixXd b = MatrixXd::Zero(n, 3);
    // Define saturation matrix and its inverse (local variables)
    MatrixXd sat(3, 3);
    sat << 0.64, 0.8, 1,
           1,    1,   1,
           1.44, 1.2, 1;
    MatrixXd inv_sat = sat.inverse();
    // Use a loop over each subtransient machine (use "li" for loop index)

    cout << "mac_sub_idx is : \n" << mac_sub_idx << "\n";
    cout << "bus is : \n" << bus << "\n";
    cout << "n is : " << n << "\n";  
    cout << "mac_con is : \n" << mac_con << "\n";
    cout << "busnum is : \n" << busnum << "\n";
    cout << "busnum(2) is : " << busnum(2 ,0);
    cout << "mac_sub_idx is : " << mac_sub_idx << "\n";
    cout << "mac_sub indexis " << mac_sub_idx(0) << "\n";

    for (int li = 0; li < n_sub; ++li) {
        // Avoid conflict with the function parameter "dummy" by using "idx" for the machine index
        int idx = mac_sub_idx(li, 0) - 1;
        cout << "the idx is : " << idx << "\n";
        cout << "we are here1\n";
        // Set bus number from mac_con (adjust indexing as needed)
        busnum(idx, 0) = mac_con(idx, 1) - 1;
        
        // Update mac_con values if necessary
        if (mac_con(idx, 7) != mac_con(idx, 12))
            mac_con(idx, 12) = mac_con(idx, 7);
        if (mac_con(idx, 13) == 0.0)
            mac_con(idx, 13) = 999.0;
        if (mac_con(idx, 14) == 0)
            mac_con(idx, 14) = 999.0;

        // Compute machine potential values
        cout << "we are here 6\n";
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
        cout << "we are here 7\n";

        // Get terminal voltage and angle from bus data
        eterm(idx, 0) = bus((int)busnum(idx, 0), 1);
        theta(idx, 0) = bus((int)busnum(idx, 0), 2) * M_PI / 180.0;
        cout << "we are here 8\n";

        // Compute electrical power values (Pg and Qg)
        
        pelect(idx, 0) = bus((int)busnum(idx, 0), 3) * mac_con(idx, 21);
        qelect(idx, 0) = bus((int)busnum(idx, 0), 4) * mac_con(idx, 22);
        
        cout << "we are here 9\n";

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

        cout << "we are here 8\n";

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
        cout << "we are here 9\n";

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
        cout << "we are 10 \n";
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
        cout << "we are 11 \n";

        // Compute the real and imaginary parts of the internal flux
        psi_re(idx, 0) = (-sin(mac_ang(idx, 0)) * psiqpp(idx, 0)) + (cos(mac_ang(idx, 0)) * psidpp(idx, 0));
        psi_im(idx, 0) = (cos(mac_ang(idx, 0)) * psiqpp(idx, 0)) + (sin(mac_ang(idx, 0)) * psidpp(idx, 0));
    }

}

