// #include "H_header.h"

// using namespace std;
// using namespace Eigen;

// // Define constants and global variables
// // double busmva, basrad, mach_ref;
// // MatrixXd psi_re, psi_im, cur_re, cur_im, bus_int;
// // MatrixXd mac_con, mac_pot, mac_ang, mac_spd, eqprime, edprime;
// // MatrixXd curd, curq, curdg, curqg, fld_cur;
// // MatrixXd vex, eterm, theta, ed, eq;
// // MatrixXd pmech, pelect, qelect ,phi;
// // MatrixXd dmac_ang, dmac_spd, deqprime, dedprime,mac_tra_idx,busnum, mcurmag ,E_Isat;
// // int n_tra;
// // MatrixXd pm_sig ;
// // MatrixXcd V ,curr ,eprime ,ei ,rot;
// /* 
// void mac_sub(MatrixXd bus, MatrixXd mac_con, MatrixXd bus_int, MatrixXd mac_sub_idx,
//     double i ,double k, double flag ,double n_sub, double basmva)
// {  

//  */


// void mac_tra(MatrixXd bus, MatrixXd mac_con, MatrixXd bus_int, MatrixXd mac_tra_idx,
//     double i ,double k, double flag ,double n_tra, double basmva)
//     {  
    
//     MatrixXd mac_pot(4 ,23);
//     Eigen::MatrixXd cur_re(4, 1), cur_im(4, 1), psidpp(4, 1), psikd(4, 1), psikq(4, 1), psiqpp(4, 1) ,psi_re(4 ,1), psi_im(4 ,1);
//     Eigen::MatrixXd mac_ang(4, 1), mac_spd(4, 1), eqprime(4, 1), edprime(4, 1);
//     Eigen::MatrixXd curd(4, 1), curq(4, 1), curdg(4, 1), curqg(4, 1), fld_cur(4, 1);
//     Eigen::MatrixXd vex(4, 1), eterm(4, 1), theta(4, 1), ed(4, 1), eq(4, 1);
//     Eigen::MatrixXd pmech(4, 1), pelect(4, 1), qelect(4, 1);
//     Eigen::MatrixXd dmac_ang(4, 1), dmac_spd(4, 1), deqprime(4, 1), dedprime(4, 1);
//     Eigen::MatrixXd mcurmag(4, 1);
//     Eigen::MatrixXd busnum(4, 1), phi(4, 1), eqra(4, 1), E_Isat(4, 1), edra(4, 1);
//     Eigen::MatrixXcd curr(4, 1), V(4, 1), ei(4, 1), rot(4, 1) ,eprime(4 ,1);
    
//     std::complex<double> jay(0, 1);
    
//     MatrixXd b = MatrixXd::Zero(n_tra,3);

//     MatrixXd sat(3,3);

//     sat <<  0.64, 0.8, 1,
//             1, 1, 1,
//             1.44, 1.2, 1;
    
//     MatrixXd inv_sat = sat.inverse();

//     for (int li = 0 ;li < n_tra ;++li){
        
//         int i = mac_tra_idx(li , 0) -1 ;
//         busnum(i , 0) = mac_con(i , 1) -1;

//         if(mac_con(i,13) == 0.0){
//             mac_con(i,13)  = 999.0;
//         }

//         mac_pot(i,0) = basmva / mac_con(i,2);
//         mac_pot(i,1) = 1.0;

//         eterm(i ,0) = bus((int)busnum(i , 0) ,1); //putting the v in there ..
//         theta(i ,0 ) = bus((int)busnum(i , 0), 2) * M_PI / 180.0;

//         pelect(i ,0) = (bus((int)busnum(i, 0), 3) * mac_con(i , 21));  //Pg
//         qelect(i ,0) = (bus((int)busnum(i, 0), 4) * mac_con(i , 22));  //Qg

//         curr(i) = sqrt((pelect(i ,0) * pelect(i ,0)) + (qelect(i ,0) * qelect(i, 0))) / eterm(i ,0);
//         curr(i) = curr(i) * mac_pot(i,0);

//         phi(i) = atan(qelect(i ,0) / pelect(i ,0));
        
//         V(i) = (eterm(i ,0));
//         V(i) = V(i) *  exp(theta(i,0)  * jay);

    
//         curr(i) = curr(i) * exp((theta(i , 0) - phi(i, 0)) * jay);
    
//         eprime(i ,0) = V(i ,0) + (mac_con(i,4) + jay*mac_con(i,6))*curr(i , 0);
//         ei(i) = V(i) + mac_con(i ,4) + jay * mac_con(i ,10) * curr(i ,0);


//         mac_ang(i) = atan(ei(i).imag() / ei(i).real());
//         mac_spd(i) = 1.0;

//         rot(i) = exp(-jay * mac_ang(i ,0)) * jay;

//         psi_re(i) = eprime(i).real();
//         psi_im(i) = eprime(i).imag();
        
//         eprime(i) = eprime(i) * rot(i);
    
//         edprime(i) = eprime(i).real();
//         eqprime(i) = eprime(i).imag(); 

//         curr(i) = rot(i) * curr(i);
//         mcurmag(i) = abs(curr(i));
//         pmech(i) = pelect(i ,0)* mac_pot(i ,0) + mac_con(i ,4)*(mcurmag(i) * mcurmag(i));            

//         curdg(i) = curr(i).real();
//         curqg(i) = curr(i).imag();

//         curd(i) = curdg(i) /  mac_pot(i ,0);
//         curq(i) = curqg(i) / mac_pot(i ,0);

//         V(i) = rot(i) * V(i);

//         ed(i) = V(i).real();
//         eq(i) = V(i).imag();

//         MatrixXd col_1 = inv_sat.row(0).transpose();
//         MatrixXd col_2 = inv_sat.row(1).transpose();
//         MatrixXd col_3 = inv_sat.row(2).transpose();

//         b(i ,0) = .8;
//         b(i ,1) = 1 + mac_con(i ,19);
//         b(i ,2) = 1.2 * (1 + mac_con(i, 20));

//         mac_pot(i, 2) =( b.row(i) * col_1).value(); // Dot product with the first column
//         mac_pot(i, 3) = (b.row(i) * col_2).value(); // Dot product with the second column
//         mac_pot(i, 4) = (b.row(i) * col_3).value(); // Dduct with the third column of inv_sat

//         E_Isat(i ,0 ) = (mac_pot(i ,2) *eqprime(i,0) * eqprime(i, 0)) + eqprime(i ,0) * mac_pot(i,3) + mac_pot(i,4);

//         // this if statement is removed from the mac_tra code ...
//         if(eqprime(i ,0) < .8){
//             E_Isat(i ,0) = eqprime(i, 0);
//         }

//         vex(i,0) = E_Isat(i ,0) +(mac_con(i ,5) - mac_con(i ,6))*curdg(i ,0);

//         fld_cur(i,0) = vex(i,0);

//         }       


//     cout << "theta is \n" << theta << "\n";
//     cout << "curd is \n" << curd << "\n";
//     cout << "curdg is \n" << curdg << "\n";
//     cout << "curq is \n" << curq << "\n";
//     cout << "curqg is \n" << curqg << "\n";
//     cout << "ed is \n" << ed << "\n";
//     cout << "edprime is \n" << edprime << "\n";
//     cout << "eq is \n" << eq << "\n";
//     cout << "eqprime is \n" << eqprime << "\n";
//     cout << "etern  is \n" << eterm << "\n";
//     cout << "mac_ang  is \n" << mac_ang << "\n";
//     cout << "mac_spd  is \n" << mac_spd << "\n";
//     cout << "pelect  is \n" << pelect << "\n";
//     cout << "qelect  is \n" << qelect << "\n";
//     cout << "pmetch  is \n" << pmech << "\n";
//     cout << "phi  is \n" << phi << "\n";

//     cout << "psi_im  is \n" << psi_im  << "\n";
//     cout << "psi_re  is \n" << psi_re  << "\n";
    
//     cout << "vex  is \n" << vex   << "\n";
    
//     cout << "rot_re   is \n" << rot.real()   << "\n";
//     cout << "rot_im   is \n" << rot.imag()   << "\n";

//     cout << "curr_re  is \n" << curr.real()  << "\n";
//     cout << "curr_im is \n" << curr.imag()  << "\n";

//     cout << "ei_re  is \n" << ei.real()  << "\n";
//     cout << "ei_im  is \n" << ei.imag()  << "\n";
//     cout << "eprime_re is \n" << eprime.real() << "\n";
//     cout << "eprime_im is \n" << eprime.imag() << "\n";
    
//     cout << "v_re  is \n" << V.real()  << "\n"; 
//     cout << "v_im  is \n" << V.imag()  << "\n";
//     cout << "E_isat is \n" << E_Isat << "\n"; 
//     cout << "fldcur\n" << fld_cur << "\n"; 

// }
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
    // Convert n_tra (double) to int for use as the number of rows
    int n = static_cast<int>(n_tra);

    // Instead of declaring with fixed sizes, we resize all output matrices to use n rows.
    // mac_pot.resize(n, 23);
    // cur_re.resize(n, 1);
    // cur_im.resize(n, 1);
    // psidpp.resize(n, 1);
    // psikd.resize(n, 1);
    // psikq.resize(n, 1);
    // psiqpp.resize(n, 1);
    // psi_re.resize(n, 1);
    // psi_im.resize(n, 1);
    // mac_ang.resize(n, 1);
    // mac_spd.resize(n, 1);
    // eqprime.resize(n, 1);
    // edprime.resize(n, 1);
    // curd.resize(n, 1);
    // curq.resize(n, 1);
    // curdg.resize(n, 1);
    // curqg.resize(n, 1);
    // fld_cur.resize(n, 1);
    // vex.resize(n, 1);
    // eterm.resize(n, 1);
    // theta.resize(n, 1);
    // ed.resize(n, 1);
    // eq.resize(n, 1);
    // pmech.resize(n, 1);
    // pelect.resize(n, 1);
    // qelect.resize(n, 1);
    // dmac_ang.resize(n, 1);
    // dmac_spd.resize(n, 1);
    // deqprime.resize(n, 1);
    // dedprime.resize(n, 1);
    // mcurmag.resize(n, 1);
    // busnum.resize(n, 1);
    // phi.resize(n, 1);
    // eqra.resize(n, 1);
    // E_Isat.resize(n, 1);
    // edra.resize(n, 1);
    // curr.resize(n, 1);
    // V.resize(n, 1);
    // ei.resize(n, 1);
    // rot.resize(n, 1);
    // Local intermediate matrix b (n x 3)
    MatrixXd b = MatrixXd::Zero(n, 3);

    // Define the saturation matrix and compute its inverse.
    MatrixXd sat(3, 3);
    sat <<  0.64, 0.8, 1,
            1,    1,   1,
            1.44, 1.2, 1;
    MatrixXd inv_sat = sat.inverse();

    std::complex<double> jay(0, 1);

    // Loop over each transient machine
    for (int li = 0; li < n; ++li) {
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

    // Print selected outputs (unchanged from original)
    cout << "result in mac_Tra is :----- \n";
    cout << "theta is \n" << theta << "\n";
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
    cout << "pmech  is \n" << pmech << "\n";
    cout << "phi  is \n" << phi << "\n";
    cout << "psi_im  is \n" << psi_im << "\n";
    cout << "psi_re  is \n" << psi_re << "\n";
    cout << "vex  is \n" << vex << "\n";
    cout << "rot_re   is \n" << rot.real() << "\n";
    cout << "rot_im   is \n" << rot.imag() << "\n";
    cout << "curr_re  is \n" << curr.real() << "\n";
    cout << "curr_im  is \n" << curr.imag() << "\n";
    cout << "ei_re  is \n" << ei.real() << "\n";
    cout << "ei_im  is \n" << ei.imag() << "\n";
    cout << "eprime_re is \n" << eprime.real() << "\n";
    cout << "eprime_im is \n" << eprime.imag() << "\n";
    cout << "v_re  is \n" << V.real() << "\n"; 
    cout << "v_im  is \n" << V.imag() << "\n";
    cout << "E_isat is \n" << E_Isat << "\n"; 
    cout << "fldcur\n" << fld_cur << "\n"; 
}


