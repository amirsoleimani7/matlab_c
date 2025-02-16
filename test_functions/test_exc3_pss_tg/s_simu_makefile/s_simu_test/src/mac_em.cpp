// #include "H_header.h"

// using namespace std;
// using namespace Eigen;

// // mac_em gets bus , mac_con , bus_int , mac_em_idx , other
// void mac_em(MatrixXd bus ,MatrixXd mac_con ,MatrixXd bus_int ,MatrixXd mac_em_idx,
//         double i ,double k , double flag ,double n_em,double basmva)
// {
    
//     MatrixXd mac_pot(4, 2);
//     MatrixXd eterm(4, 1), pelect(4, 1), qelect(4, 1), phi(4, 1),
//             psi_re(4, 1), psi_im(4, 1), mac_ang(4, 1), mac_spd(4, 1),
//             eqprime(4, 1), vex(4, 1), edprime(4, 1), busnum(4, 1),
//             curqg(4, 1), curdg(4, 1), eq(4, 1), ed(4, 1), 
//             curq(4, 1), curd(4, 1), pmech(4, 1), theta(4, 1);

//     MatrixXcd V(4 ,1) ,curr(4 ,1) , eprime(4 ,1) , ei(4 ,1) , rot(4 ,1);

//     complex<double> jay(0.0 ,1.0); 

//     for (int lk=0;lk < n_em;++lk)
//     {
//         int li = mac_em_idx(lk , 0) -1;
        
//         busnum(li , 0) = mac_con(li , 1) -1;
//         cout << "--busnum(li) : " << busnum(li) << "\n";

//         mac_pot(li, 0) = basmva / mac_con(li ,2);
//         mac_pot(li, 1) = 1.0;

//         eterm(li ,0) = bus((int)busnum(li , 0) ,1); //putting the v in there ..
//         theta(li ,0 ) = bus((int)busnum(li , 0), 2) * M_PI / 180.0;

//         pelect(li ,0) = (bus((int)busnum(li, 0), 3) * mac_con(li , 21));  //Pg
//         qelect(li ,0) = (bus((int)busnum(li, 0), 4) * mac_con(li , 22));  //Qg

//         curr(li) = sqrt((pelect(li ,0) * pelect(li ,0)) + (qelect(li ,0) * qelect(li, 0))) / eterm(li ,0);
//         curr(li) = curr(li) * mac_pot(li,0);

//         phi(li) = atan(qelect(li ,0) / pelect(li ,0));

//         V(li) = (eterm(li ,0));
//         V(li) = V(li) *  exp(theta(li,0)  * jay);
        
//         curr(li) = curr(li) * exp((theta(li , 0) - phi(li, 0)) * jay);

//         eprime(li) = V(li ,0) + (jay * mac_con(li ,6) * curr(li ,0));

//         ei(li) = eprime(li);
//         mac_ang(li) = atan(ei(li).imag() / ei(li).real());
//         mac_spd(li) = 1.0;
        
//         rot(li) = exp(-jay * mac_ang(li ,0)) * jay;

//         psi_re(li) = eprime(li).real();
//         psi_im(li) = eprime(li).imag();
    
//         eprime(li) = rot(li) * eprime(li);

//         edprime(li) = eprime(li).real();
//         eqprime(li) = eprime(li).imag();

//         curr(li) = rot(li) * curr(li);

//         curdg(li) = curr(li).real();
//         curqg(li) = curr(li).imag();

//         curd(li) = curdg(li) /  mac_pot(li ,0);
//         curq(li) = curqg(li) / mac_pot(li ,0);

//         V(li) = rot(li) * V(li);
//         ed(li) = V(li).real();
//         eq(li) = V(li).imag();

//         vex(li) = eqprime(li ,0);

//         pmech(li , 0) = (pelect(li ,0) * mac_pot(li ,0));        
//     }

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

//     cout << "eprime_re  is \n" << eprime.real()  << "\n";
//     cout << "eprime_im  is \n" << eprime.imag()  << "\n";

//     cout << "v_re  is \n" << V.real()  << "\n";
//     cout << "v_im  is \n" << V.imag()  << "\n";

// }

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
    // Convert n_em to integer for resizing
    int n = static_cast<int>(n_em);
    
    // // Resize all output matrices using conservativeResize to preserve any existing data
    // mac_pot.conservativeResize(n, 2);
    // eterm.conservativeResize(n, 1);
    // pelect.conservativeResize(n, 1);
    // qelect.conservativeResize(n, 1);
    // phi.conservativeResize(n, 1);
    // psi_re.conservativeResize(n, 1);
    // psi_im.conservativeResize(n, 1);
    // mac_ang.conservativeResize(n, 1);
    // mac_spd.conservativeResize(n, 1);
    // eqprime.conservativeResize(n, 1);
    // vex.conservativeResize(n, 1);
    // edprime.conservativeResize(n, 1);
    // busnum.conservativeResize(n, 1);
    // curqg.conservativeResize(n, 1);
    // curdg.conservativeResize(n, 1);
    // eq.conservativeResize(n, 1);
    // ed.conservativeResize(n, 1);
    // curq.conservativeResize(n, 1);
    // curd.conservativeResize(n, 1);
    // pmech.conservativeResize(n, 1);
    // theta.conservativeResize(n, 1);
    
    // V.conservativeResize(n, 1);
    // curr.conservativeResize(n, 1);
    // eprime.conservativeResize(n, 1);
    // ei.conservativeResize(n, 1);
    // rot.conservativeResize(n, 1);
    
    // Local constant for complex number
    complex<double> jay(0.0, 1.0); 

    // Loop over each electromagnetic machine
    for (int lk = 0; lk < n_em; ++lk)
    {
        int li = mac_em_idx(lk, 0) - 1;
        
        busnum(li, 0) = mac_con(li, 1) - 1;
        cout << "--busnum(li) : " << busnum(li) << "\n";

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

    // cout << "theta is \n" << theta << "\n";
    // cout << "curd is \n" << curd << "\n";
    // cout << "curdg is \n" << curdg << "\n";
    // cout << "curq is \n" << curq << "\n";
    // cout << "curqg is \n" << curqg << "\n";
    // cout << "ed is \n" << ed << "\n";
    // cout << "edprime is \n" << edprime << "\n";
    // cout << "eq is \n" << eq << "\n";
    // cout << "eqprime is \n" << eqprime << "\n";
    // cout << "etern  is \n" << eterm << "\n";
    // cout << "mac_ang  is \n" << mac_ang << "\n";
    // cout << "mac_spd  is \n" << mac_spd << "\n";
    // cout << "pelect  is \n" << pelect << "\n";
    // cout << "qelect  is \n" << qelect << "\n";
    // cout << "pmetch  is \n" << pmech << "\n";
    // cout << "phi  is \n" << phi << "\n";
}
