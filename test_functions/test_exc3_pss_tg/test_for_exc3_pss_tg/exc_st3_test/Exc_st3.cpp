#include "H_header.h"

using namespace Eigen;
using namespace std;

void exc_st3(
    MatrixXd &exc_con, const MatrixXd &mac_con,const MatrixXd &mac_pot, const MatrixXd &bus_int, 
    const MatrixXd &mac_int, const MatrixXd &vex, const MatrixXd &pelect, 
    const MatrixXd &qelect, const MatrixXd &eterm, const MatrixXd &theta, 
    const MatrixXd &fldcur, MatrixXd &Efd, MatrixXd &exc_pot, 
    MatrixXd &V_B, MatrixXd &V_R, MatrixXd &V_A, MatrixXd &V_As, 
    MatrixXd &V_TR, MatrixXd &R_f, const MatrixXd &st3_idx, 
    const MatrixXd &st3_TB_idx)

{


    int n_st3 = st3_idx.rows(); // or given in the funtion parameters .. 
    MatrixXd n(n_st3 ,1);
    MatrixXd n_bus(n_st3 ,1);
    MatrixXd TB(n_st3 , 1);
    MatrixXd V_I(n_st3 , 1);


    MatrixXd low_IN(0 ,1); // these change dynamicly as well ... 
    MatrixXd big_IN(0 ,1);
    MatrixXd mid_IN(0 ,1);

    int n_sub = 1; 
    int n_tra = 1;

    const std::complex<double> jay(0, 1); 

    
    // some errors lines here is needed (but it's only for the non vectorized one ... )

    if(n_sub == 0 && n_tra == 0){
        cout << "error in exc_st3\n";
        cout << "you must have either subtransient or transient generator models\n";
    }

    // this is the vectorized implementation  ... 

    MatrixXd V_E = MatrixXd::Zero(n_st3, 1); // based on 
    MatrixXd I_N = V_E;
    MatrixXcd iterm = V_E; //this is a complex matrix 
    MatrixXcd vep = V_E;
    MatrixXcd ve = V_E;
    MatrixXd F_EX = V_E;
    MatrixXd ve_low(0 ,1) ; // the size changes dynamicly ...   



    //TO DO : low_IN should be a matrix
    // big_IN , mid_IN , fex_error , nKA_idx  , max_VI , 

    exc_pot.resize(n_st3 ,5);
    V_A.resize(n_st3 ,1);
    V_As.resize(n_st3 , 1);
    V_B.resize(n_st3 , 1);
    V_R.resize(n_st3 ,1);
    V_TR.resize(n_st3 ,1);
    R_f.resize(n_st3 ,1);
    Efd.resize(n_st3 , 1);


    for(int li = 0 ; li < n_st3 ; ++li){
        // Machine number vector
        int lj = st3_idx(li , 0) -1;

        n(li , 0) = mac_int((int)exc_con(lj , 1) -1 , 0); // probabbly needs to be 0-based .. // n is a matrix

        n_bus(li , 0) = bus_int((int)mac_con((int)n(li , 0) -1 ,1) -1); // n_bus is a matrix

        Efd((int)n(li , 0) -1  ,0) = vex((int)n(li , 0) -1  ,0);

        if (Efd((int)n(li ,0) -1 , 0) > exc_con(lj , 17)){ // check for max_lim ... 
            cout << "EXC_ST3: Efd exceeds maximum in initialization at " << n(li ,0)-1  << "\n";
        }
        
        exc_pot(lj , 0) = exc_con(lj , 12) * cos(exc_con(lj , 13) * M_PI / 180); // exc_con(lj , 12) is qP(lj , 0) ..
        exc_pot(lj , 1) = exc_con(lj , 12) * sin(exc_con(lj , 13) * M_PI / 180); // exc_con(lj , 13) is KP(lj ,0) ... 


        iterm((int)n(li ,0) -1 , 0) = (pelect((int)n(li ,0) -1, 0) - jay * qelect((int)n(li ,0) -1 , 0)) /
                (eterm((int)n(li ,0) -1, 0) * exp(-jay * theta((int)n_bus(lj ,0) -1 , 0))) *
                mac_pot((int)n(li , 0) -1 ,0);

        vep((int)n(li, 0) -1 ,0) = eterm((int)n(li, 0) -1, 0) * exp(jay * theta((int)n_bus(li, 0) -1, 0)) * // not sure about the usage of n_bus
            (exc_pot(lj, 0) + jay * exc_pot(lj, 1)); //not sure about the lj or n index in the exc_pot ... 


        ve((int)n(li, 0) -1,0) = vep((int)n(li, 0)-1  , 0) + jay * (exc_con(lj, 14) +
            (exc_pot(lj, 0) + jay * exc_pot(lj, 1)) *
            exc_con(lj, 15)) * iterm((int)n(li , 0)-1 , 0); // the indexing is baed on the doucment not the matlab code 


        V_E(li ,0) = abs(ve(li , 0)); // not sure about this eather ... 

        if(V_E(li , 0) < 1e-6){
            ve_low.conservativeResize(ve_low.rows() +1  ,NoChange);
            ve_low(ve_low.rows() -1 , 0) = li; // THESE ARE THE INDEXES ... 
        }

        // if(V_E((int)n(li ,0) , 0) <1e-06){ // this should be usig ve_low .. 
        //     cout << "not sure about the error code here \n";
        // }
        
        I_N((int)n(li, 0) -1 ,0) = exc_con(lj, 16) * fldcur((int)n(li  ,0 ) -1, 0) / V_E((int)n(li , 0)-1 ,0);


        if(I_N((int)n(li , 0) -1 ,0) < 0.433){
            
            low_IN.conservativeResize(low_IN.rows() +1 , NoChange);
            low_IN(low_IN.rows() -1 , 0) = n(li , 0);
            F_EX((int)n(li , 0) -1 ,0) = 1 -0.5771 * I_N((int)n(li ,0) -1, 0);
        }

        else if(I_N((int)n(li , 0) -1 ,0) > 0.75){
            big_IN.conservativeResize(big_IN.rows() +1 , NoChange);
            big_IN(big_IN.rows() -1 , 0) = n(li , 0);
            F_EX((int)n(li , 0) -1 ,0) = 1.708 * (1 - I_N((int)n(li , 0)-1  ,0));
        }

        else{ // SOME THING BETWEEN .433 < I < .75 ...
            mid_IN.conservativeResize(mid_IN.rows() +1 , NoChange);
            mid_IN(mid_IN.rows() -1 , 0) = n(li , 0);
            F_EX((int)n(li ,0) -1 ,0) = pow((.75 * (1 - pow(I_N((int)n(li ,0) -1  ,0 ) , 2))) , .5); // make sure of this one ... 
        }
        

        if(F_EX((int)n(li ,0) -1,0) <= 0){
            cout << "the F_EX(" << (int)n(li ,0) -1 << ",0)" << "\n";
        }


        
        V_B(lj, 0) = V_E((int)n(li ,0) -1,0) * F_EX((int)n(li ,0) -1,0);
        
        V_R(lj, 0) = Efd(lj, 0) / V_B(lj , 0);

        if(exc_con(lj , 3) == 0){
            exc_con(lj , 3) = 1; // this is the KA(lj, 0)
        }
        

        V_A(lj, 0) = V_R(lj, 0) / exc_con(lj, 3) +  // not sure about this 
                                            min(exc_con(lj, 19), exc_con(lj , 18)* Efd(lj,0));


        V_As(lj, 0) = V_A(lj, 0);
        exc_pot(lj, 4) = 1;


        TB(lj ,0) = st3_TB_idx(lj ,0);  

        exc_pot((int)TB(lj ,0)-1  ,4) = exc_con((int)TB(lj ,0) -1 , 6) / exc_con((int)TB(lj ,0)-1 , 5);


        V_I((int)n(li , 0) -1 ,0) = V_A(lj , 0) / exc_con(lj , 11);

        if(V_I((int)n(li ,0) -1,0) > exc_con(lj , 9)) {
            cout << "cEXC_ST3: V_I above maximum in initialization at\n ";
        }

        if(V_I((int)n(li ,0) -1,0) < exc_con(lj , 10)){
            cout << "EXC_ST3: V_I below minimum in initialization at\n";
        }

        exc_pot(lj ,2) = eterm((int)n(li ,0) -1,0) + V_I((int)n(li , 0) -1 ,0);
        V_TR(lj , 0) = eterm((int)n(li , 0) -1, 0);
        R_f(lj , 0) = 0;
    }
    
    cout << "-------------resalt---------------\n ";
    cout << "V_E IS : \n" << V_E << "\n";
    cout << "I_N is : \n" << I_N << "\n";
    cout << "iterm is : \n" << iterm << "\n";
    cout << "vep is : \n" << vep << "\n";
    cout << "ve is : \n" << ve << "\n";
    cout << "F_EX is : \n" << F_EX << "\n";
    cout << "n_bus is : \n" << n_bus << "\n";
    cout << "n is : \n" << n << "\n";
    cout << "Efd is : \n" << Efd << "\n";
    cout << "exc_pot is : \n" << exc_pot << "\n";
    cout << "low_IN is : \n" << low_IN << "\n";
    cout << "V_B is : \n" << V_B << "\n";
    cout << "V_R is : \n" << V_R << "\n";
    cout << "V_A is : \n" << V_A << "\n";
    cout << "V_As is : \n" << V_As << "\n";
    cout << "V_I is : \n" << V_I << "\n";
    cout << "V_TR is : \n" << V_TR << "\n";
    cout << "V_f is : \n" << R_f << "\n";
 
}