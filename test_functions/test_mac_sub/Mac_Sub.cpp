#include "H_header.h"
#include <sched.h>
using namespace std;
using namespace Eigen;

double busmva, basrad, mach_ref;
MatrixXd psi_re, psi_im, cur_re, cur_im, bus_int, psidpp , psikd, psikq ,psiqpp;
MatrixXd mac_con, mac_pot, mac_ang, mac_spd, eqprime, edprime;
MatrixXd curd, curq, curdg, curqg, fld_cur;
MatrixXd vex, eterm, theta, ed, eq;
MatrixXd pmech, pelect, qelect;
MatrixXd dmac_ang, dmac_spd, deqprime, dedprime;
MatrixXd mac_sub_idx , mcurmag;
MatrixXd busnum , phi ,eqra ,E_Isat ,edra;
MatrixXcd curr ,V ,ei ,rot ;
int n_sub;
int n_tra;
double basmva;
MatrixXd pm_sig;

void mac_sub(int i, int k, MatrixXd& bus, int flag){

        complex<double> jay(0.0, 1.0);

        MatrixXd bus_num = MatrixXd::Zero(n_sub,1);
        MatrixXd b = MatrixXd::Zero(n_sub,3);

        MatrixXd sat(3,3);

        sat <<  0.64, 0.8, 1,
                1, 1, 1,
                1.44, 1.2, 1;

        MatrixXd inv_sat = sat.inverse();

        for (int li = 0 ;li < n_sub ;++li){

            int i = mac_sub_idx(li ,0) -1;

            busnum(i , 0) = mac_con(i , 1) -1;

            if(mac_con(i,7) != mac_con(i,12)){
                mac_con(i,12) = mac_con(i,7);   
            }

            if(mac_con(i,13) == 0.0){
                mac_con(i,13)  = 999.0;
            }
            
            if(mac_con(i,14) == 0){
                mac_con(i,14) = 999.0;
            }
            mac_pot(i ,0) = basmva/mac_con(i ,2);            
            mac_pot(i,1) = 1.0;
 
            //-------------------------------------
            //not sure about the mac_pot or that mac_con in the below code
            //just leave it for now

            mac_pot(i, 7) = mac_con(i, 6) - mac_con(i, 3);     //this is checked ...
            mac_pot(i, 8) = (mac_con(i, 7) - mac_con(i, 3)) / mac_pot(i, 7);    //this is checked ...
            mac_pot(i, 6) = (mac_con(i, 5) - mac_con(i, 6)) * mac_pot(i, 8);    //matlab cheacked ,documents checked , diagram nope
            mac_pot(i, 9) = (mac_con(i, 6) - mac_con(i, 7)) / mac_pot(i, 7);   //matlab , doc , not diagram
            mac_pot(i, 5) = (mac_con(i, 5) - mac_con(i, 6)) / mac_pot(i, 7) * mac_pot(i, 9);   //matalb ,doc , the (/) operation is wrong in digram ..
            mac_pot(i, 12) = mac_con(i, 11) - mac_con(i, 3);    //this is cheacked ..
            mac_pot(i, 13) = (mac_con(i, 12) - mac_con(i, 3)) / mac_pot(i, 12); //not checked ...
            mac_pot(i, 11) = (mac_con(i, 10) - mac_con(i, 11)) * mac_pot(i, 13); //this is checked ...
            mac_pot(i, 14) = (mac_con(i, 11) - mac_con(i, 12)) / mac_pot(i, 12);    //checked
            mac_pot(i, 10) = (mac_con(i, 10) - mac_con(i, 11)) / mac_pot(i, 12) * mac_pot(i, 14);   //diagram just ...
            
            //--------------------------------------
            eterm(i ,0) = bus((int)busnum(i , 0) ,1); //putting the v in there ..
            theta(i ,0 ) = bus((int)busnum(i , 0), 2) * M_PI / 180.0;

            pelect(i ,0) = (bus((int)busnum(i, 0), 3) * mac_con(i , 21));  //Pg
            qelect(i ,0) = (bus((int)busnum(i, 0), 4) * mac_con(i , 22));  //Qg

            curr(i) = sqrt((pelect(i ,0) * pelect(i ,0)) + (qelect(i ,0) * qelect(i, 0))) / eterm(i ,0);
            curr(i) = curr(i) * mac_pot(i,0);

            phi(i) = atan(qelect(i ,0) / pelect(i ,0));

            curr(i) = curr(i) * exp((theta(i , 0) - phi(i, 0)) * jay);
            
            V(i) = (eterm(i ,0));
            V(i) = V(i) *  exp(theta(i,0)  * jay);
    
            curr(i) = curr(i) * exp((theta(i , 0) - phi(i, 0)) * jay);

            ei(i) = V(i) + mac_con(i ,4) + jay * mac_con(i ,10) * curr(i ,0);
            mac_ang(i) = atan(ei(i).imag() / ei(i).real());
            mac_spd(i) = 1.0;
            rot(i) = exp(-jay * mac_ang(i ,0)) * jay;
            curr(i) = rot(i) * curr(i);
            curdg(i) = curr(i).real();
            curqg(i) = curr(i).imag();
            
            curd(i) = curdg(i) /  mac_pot(i ,0);
            curq(i) = curqg(i) / mac_pot(i ,0);

            mcurmag(i) = abs(curr(i));
            pmech(i) = pelect(i ,0)* mac_pot(i ,0) + mac_con(i ,4)*(mcurmag(i) * mcurmag(i));            
            V(i) = rot(i) * V(i);
            ed(li) = V(li).real();
            eq(li) = V(li).imag();
            eqra(i) = eq(i ,0) + mac_con(i ,4) * curqg(i ,0);
            psidpp(i) = eqra(i) + mac_con(i,7)*curdg(i,0);
            psikd(i,0) = eqra(i) + mac_con(i,3 )*curdg(i,0);
            eqprime(i,0) = eqra(i) + mac_con(i,6)*curdg(i,0);
            edra(i ,0) = -ed(i,0) - mac_con(i,4)*curdg(i,0);
            psiqpp(i ,0) = edra(i ,0) + mac_con(i,12)*curqg(i,0);
            psikq(i,0) = edra(i ,0) + mac_con(i,3)*curqg(i,0);
            edprime(i,0) = edra(i ,0) + mac_con(i,11)*curqg(i,0);

            MatrixXd col_1 = inv_sat.transpose().col(0);
            MatrixXd col_2 = inv_sat.transpose().col(1);
            MatrixXd col_3 = inv_sat.transpose().col(2);

            MatrixXd b(n_sub ,3);
            for(int li = 0;li < n_sub ;++li){
                b(li ,0) = .8;
                b(li ,1) = 1 + mac_con(li ,19);
                b(li ,2) = 1.2 + mac_con(li ,20);
            }

            mac_pot(i,2) =  b.dot(col_1);
            mac_pot(i,3) =  b.dot(col_2);
            mac_pot(i,4) =  b.dot(col_3);

            E_Isat(i ,0 ) = (eqprime(i,0) * eqprime(i, 0) * mac_pot(i ,2)) + (eqprime(i ,0) * mac_pot(i,3))  +mac_pot(i,4);

            // this if statement is removed from the mac_tra code ...
            if(E_Isat(i ,0) < .8){
                E_Isat(i ,0) = eqprime(i);
            }
    
            vex(i,0) = E_Isat(i) + mac_con(i,5) * (eqprime(i ,0)  - psikd(i ,0)) +  mac_con(i,6) * curdg(i, 0) ;
        
            fld_cur(i,1)  =vex(i,1);

            psi_re(i ,0) = (sin(mac_ang(i ,0)) * psiqpp(i ,0) * (-1)) + (cos(mac_ang(i ,0)) *psidpp(i ,0));
            psi_im(i ,0) = (-cos(mac_ang(i)) * -psiqpp(i ,0)) + (sin(mac_ang(i, 0)) *psidpp(i ,0));
        }
        

















}
