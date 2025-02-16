// #include "H_header.h"

// using namespace std;
// using namespace Eigen;

// /* 
// void mac_em(MatrixXd bus ,MatrixXd mac_con ,MatrixXd bus_int ,MatrixXd mac_em_idx,
//         double i ,double k , double flag ,double n_em,double basmva)
// {
//  */
// void mac_sub( int i , int flag, MatrixXd bus, MatrixXd mac_con, MatrixXd bus_int, MatrixXd mac_sub_idx ,double n_sub, double basmva)
// {  
//         MatrixXd mac_pot(4 ,23);
//         Eigen::MatrixXd cur_re(4, 1), cur_im(4, 1), psidpp(4, 1), psikd(4, 1), psikq(4, 1), psiqpp(4, 1) ,psi_re(4 ,1), psi_im(4 ,1);
//         Eigen::MatrixXd mac_ang(4, 1), mac_spd(4, 1), eqprime(4, 1), edprime(4, 1);
//         Eigen::MatrixXd curd(4, 1), curq(4, 1), curdg(4, 1), curqg(4, 1), fld_cur(4, 1);
//         Eigen::MatrixXd vex(4, 1), eterm(4, 1), theta(4, 1), ed(4, 1), eq(4, 1);
//         Eigen::MatrixXd pmech(4, 1), pelect(4, 1), qelect(4, 1);
//         Eigen::MatrixXd dmac_ang(4, 1), dmac_spd(4, 1), deqprime(4, 1), dedprime(4, 1);
//         Eigen::MatrixXd mcurmag(4, 1);
//         Eigen::MatrixXd busnum(4, 1), phi(4, 1), eqra(4, 1), E_Isat(4, 1), edra(4, 1);
//         Eigen::MatrixXcd curr(4, 1), V(4, 1), ei(4, 1), rot(4, 1);
//         complex<double> jay(0.0, 1.0);
//         int k = 0;
//         MatrixXd b = MatrixXd::Zero(n_sub,3);
//         // for(int i = 0 ; i < n_sub ;++i){
//         //     b(i ,0) = .8;
//         //     b(i ,1) = 1 + mac_con(i ,19);
//         //     b(i ,2) = 1.2 * (1 + mac_con(i, 20));
//         // }

//         MatrixXd sat(3,3);

//         sat <<  0.64, 0.8, 1,
//                 1, 1, 1,    
//                 1.44, 1.2, 1;

//         MatrixXd inv_sat = sat.inverse();

//         for (int li = 0 ;li < n_sub ;++li){

//             int i = mac_sub_idx(li ,0) -1;
//             busnum(i , 0) = mac_con(i , 1) -1;

//             if(mac_con(i,7) != mac_con(i,12)){
//                 mac_con(i,12) = mac_con(i,7);   
//             }

//             if(mac_con(i,13) == 0.0){
//                 mac_con(i,13)  = 999.0;
//             }
            
//             if(mac_con(i,14) == 0){
//                 mac_con(i,14) = 999.0;
//             }

//             mac_pot(i ,0) = basmva/mac_con(i ,2);            
//             mac_pot(i,1) = 1.0;

//             mac_pot(i, 7) = mac_con(i, 6) - mac_con(i, 3);     //this is checked ...
//             mac_pot(i, 8) = (mac_con(i, 7) - mac_con(i, 3)) / mac_pot(i, 7);    //this is checked ...
//             mac_pot(i, 6) = (mac_con(i, 5) - mac_con(i, 6)) * mac_pot(i, 8);    //matlab cheacked ,documents checked , diagram nope
//             mac_pot(i, 9) = (mac_con(i, 6) - mac_con(i, 7)) / mac_pot(i, 7);   //matlab , doc , not diagram
//             mac_pot(i, 5) = (mac_con(i, 5) - mac_con(i, 6)) / mac_pot(i, 7) * mac_pot(i, 9);   //matalb ,doc , the (/) operation is wrong in digram ..
//             mac_pot(i, 12) = mac_con(i, 11) - mac_con(i, 3);    //this is cheacked ..
//             mac_pot(i, 13) = (mac_con(i, 12) - mac_con(i, 3)) / mac_pot(i, 12); //not checked ...
//             mac_pot(i, 11) = (mac_con(i, 10) - mac_con(i, 11)) * mac_pot(i, 13); //this is checked ...
//             mac_pot(i, 14) = (mac_con(i, 11) - mac_con(i, 12)) / mac_pot(i, 12);    //checked
//             mac_pot(i, 10) = (mac_con(i, 10) - mac_con(i, 11)) / mac_pot(i, 12) * mac_pot(i, 14);   //diagram just ...
            
//             eterm(i ,0) = bus((int)busnum(i , 0) ,1); //putting the v in there ..
//             theta(i ,0 ) = bus((int)busnum(i , 0), 2) * M_PI / 180.0;

//             pelect(i ,0) = (bus((int)busnum(i, 0), 3) * mac_con(i , 21));  //Pg
//             qelect(i ,0) = (bus((int)busnum(i, 0), 4) * mac_con(i , 22));  //Qg

//             curr(i) = sqrt((pelect(i ,0) * pelect(i ,0)) + (qelect(i ,0) * qelect(i, 0))) / eterm(i ,0);
//             curr(i) = curr(i) * mac_pot(i,0);

//             phi(i) = atan(qelect(i ,0) / pelect(i ,0));

            
//             V(i) = (eterm(i ,0));
//             V(i) = V(i) *  exp(theta(i,0)  * jay);
    
//             curr(i) = curr(i) * exp((theta(i , 0) - phi(i, 0)) * jay);

//             ei(i) = V(i) + mac_con(i ,4) + jay * mac_con(i ,10) * curr(i ,0);

//             mac_ang(i) = atan(ei(i).imag() / ei(i).real());
//             mac_spd(i) = 1.0;
            
//             rot(i) = exp(-jay * mac_ang(i ,0)) * jay;
//             curr(i) = rot(i) * curr(i);

//             curdg(i) = curr(i).real();
//             curqg(i) = curr(i).imag();

//             curd(i) = curdg(i) /  mac_pot(i ,0);
//             curq(i) = curqg(i) / mac_pot(i ,0);

//             mcurmag(i) = abs(curr(i));
//             pmech(i) = pelect(i ,0)* mac_pot(i ,0) + mac_con(i ,4)*(mcurmag(i) * mcurmag(i));            
            
//             V(i) = rot(i) * V(i);
            
//             ed(i) = V(i).real();
//             eq(i) = V(i).imag();

//             eqra(i) = eq(i ,0) + mac_con(i ,4) * curqg(i ,0);
            
//             psidpp(i) = eqra(i) + mac_con(i,7)*curdg(i,0);
            
//             psikd(i,0) = eqra(i) + mac_con(i,3 )*curdg(i,0);
            
//             eqprime(i,0) = eqra(i) + mac_con(i,6)*curdg(i,0);
            
//             edra(i ,0) = -ed(i,0) - mac_con(i,4)*curdg(i,0);

//             psiqpp(i ,0) = edra(i ,0) + mac_con(i,12)*curqg(i,0);
            
//             psikq(i,0) = edra(i ,0) + mac_con(i,3)*curqg(i,0);
            
//             edprime(i,0) = edra(i ,0) + mac_con(i,11)*curqg(i,0);

//             MatrixXd col_1 = inv_sat.row(0).transpose();
//             MatrixXd col_2 = inv_sat.row(1).transpose();
//             MatrixXd col_3 = inv_sat.row(2).transpose();

//             b(i ,0) = .8;
//             b(i ,1) = 1 + mac_con(i ,19);
//             b(i ,2) = 1.2 * (1 + mac_con(i, 20));

//             mac_pot(i, 2) =( b.row(i) * col_1).value(); // Dot product with the first column
//             mac_pot(i, 3) = (b.row(i) * col_2).value(); // Dot product with the second column
//             mac_pot(i, 4) = (b.row(i) * col_3).value(); // Dduct with the third column of inv_sat

//             E_Isat(i ,0 ) = (mac_pot(i ,2) *eqprime(i,0) * eqprime(i, 0)) + eqprime(i ,0) * mac_pot(i,3) + mac_pot(i,4);

//             // this if statement is removed from the mac_tra code ...
//             if(eqprime(i ,0) < .8){
//                 E_Isat(i ,0) = eqprime(i, 0);
//             }
    
//             vex(i,0) = E_Isat(i ,0) + mac_pot(i,5) * (eqprime(i ,0)  - psikd(i ,0)) +  mac_pot(i,6) * curdg(i, 0) ;

//             fld_cur(i,0) = vex(i,0);

//             psi_re(i ,0) = (sin(mac_ang(i ,0)) * psiqpp(i ,0) * (-1)) + (cos(mac_ang(i ,0)) *psidpp(i ,0));
//             psi_im(i ,0) = (-cos(mac_ang(i)) * -psiqpp(i ,0)) + (sin(mac_ang(i, 0)) *psidpp(i ,0));
//         }


     
//         cout << "theta is \n" << theta << "\n";
//         cout << "curd is \n" << curd << "\n";
//         cout << "curdg is \n" << curdg << "\n";
//         cout << "curq is \n" << curq << "\n";
//         cout << "curqg is \n" << curqg << "\n";
//         cout << "ed is \n" << ed << "\n";
//         cout << "edprime is \n" << edprime << "\n";
//         cout << "eq is \n" << eq << "\n";
//         cout << "eqprime is \n" << eqprime << "\n";
//         cout << "etern  is \n" << eterm << "\n";
//         cout << "mac_ang  is \n" << mac_ang << "\n";
//         cout << "mac_spd  is \n" << mac_spd << "\n";
//         cout << "pelect  is \n" << pelect << "\n";
//         cout << "qelect  is \n" << qelect << "\n";
//         cout << "pmetch  is \n" << pmech << "\n";
//         cout << "phi  is \n" << phi << "\n";

//         cout << "psi_im  is \n" << psi_im  << "\n";
//         cout << "psi_re  is \n" << psi_re  << "\n";
        
//         cout << "vex  is \n" << vex   << "\n";
        
//         cout << "rot_re   is \n" << rot.real()   << "\n";
//         cout << "rot_im   is \n" << rot.imag()   << "\n";

//         cout << "curr_re  is \n" << curr.real()  << "\n";
//         cout << "curr_im is \n" << curr.imag()  << "\n";

//         cout << "ei_re  is \n" << ei.real()  << "\n";
//         cout << "ei_im  is \n" << ei.imag()  << "\n";
        
//         cout << "eqra is \n" << eqra << "\n";
//         cout << "psidpp is \n" << psidpp << "\n";
//         cout << "psikd is \n" << psikd << "\n";
//         cout << "edra is \n" << edra << "\n";
//         cout << "psiqpp is \n" << psiqpp << "\n";
//         cout << "psikq is \n" << psikq << "\n";
//         cout << "v_re  is \n" << V.real()  << "\n";
//         cout << "v_im  is \n" << V.imag()  << "\n";
//         cout << "i_esat \n" << E_Isat << "\n";
//         cout << "fldcur\n" << fld_cur << "\n"; 
    
// }


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
    
    // Resize all output matrices based on n_sub (convert n_sub to int)

    int n = static_cast<int>(n_sub);
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

    // Local intermediate matrix b (n x 3)
    MatrixXd b = MatrixXd::Zero(n, 3);
    cout << "we are here 3\n";
    // Define saturation matrix and its inverse (local variables)
    MatrixXd sat(3, 3);
    sat << 0.64, 0.8, 1,
           1,    1,   1,
           1.44, 1.2, 1;
    MatrixXd inv_sat = sat.inverse();
    cout << "we are here 4 \n";
    // Use a loop over each subtransient machine (use "li" for loop index)

    cout << "mac_sub_idx is : \n" << mac_sub_idx << "\n";
    cout << "bus is : \n" << bus << "\n";
    for (int li = 0; li < n; ++li) {
        // Avoid conflict with the function parameter "dummy" by using "idx" for the machine index
        int idx = mac_sub_idx(li, 0) - 1;
        cout << "the idx is : " << idx << "\n";
        
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

