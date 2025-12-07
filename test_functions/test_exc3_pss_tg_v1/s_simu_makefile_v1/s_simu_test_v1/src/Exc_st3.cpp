#include "../include/H_header.h"

using namespace Eigen;
using namespace std;

void exc_st3( int i, int flag, int n_sub , int n_tra , 
    MatrixXd &exc_con, 
    const MatrixXd &mac_con,
    const MatrixXd &mac_pot, 
    const MatrixXd &bus_int, 
    const MatrixXd &mac_int, 
    const MatrixXd &vex, 
    const MatrixXd &pelect, 
    const MatrixXd &qelect, 
    const MatrixXd &eterm, 
    const MatrixXd &theta, 
    const MatrixXd &fldcur, 
    MatrixXd &Efd, 
    MatrixXd &exc_pot, 
    MatrixXd &V_B, 
    MatrixXd &V_R, 
    MatrixXd &V_A, 
    MatrixXd &V_As, 
    MatrixXd &V_TR, 
    MatrixXd &R_f, 
    const MatrixXd &st3_idx, 
    const MatrixXd &st3_TB_idx, 
    MatrixXcd &iterm,   // Output: complex matrix
    MatrixXcd &vep,     // Output: complex matrix
    MatrixXcd &ve,      // Output: complex matrix
    MatrixXd &F_EX,     
    MatrixXd &n,        // Output: machine number vector
    MatrixXd &n_bus,    // Output: bus index vector
    MatrixXd &low_IN,   // Output: list of low current indices
    MatrixXd &V_I , 
    MatrixXd &V_E, 
    MatrixXd &I_N)      // Output: V_I values
{
    

    int n_st3 = st3_idx.rows();

    n.resize(n_st3, 1);
    n_bus.resize(n_st3, 1);
    V_I.resize(n_st3, 1);
    
    // MatrixXd TB = st3_TB_idx;  // Now TB is exactly {3, 4}
    MatrixXd TB(4 ,1);
    TB = MatrixXd::Constant(4, 1, -1);  // Fill TB with -1

    // // Update TB with valid indices from st3_TB_idx.
    // // Here, we assume you want to fill the bottom two positions with the new indices.
    for (int i = 0; i < st3_TB_idx.rows(); ++i) {
        // Place the valid index into the TB; adjust this logic as needed
        TB(TB.rows() - st3_TB_idx.rows() + i, 0) = st3_TB_idx(i, 0);
    }


    low_IN.resize(0, 1);

    MatrixXd big_IN(0, 1);
    MatrixXd mid_IN(0, 1);

    const std::complex<double> jay(0, 1); 

    if(n_sub == 0 && n_tra == 0){
        cout << "error in exc_st3\n";
        cout << "you must have either subtransient or transient generator models\n";
    }

    // Local matrices used for calculations.
    V_E = MatrixXd::Zero(n_st3, 1);
    I_N = V_E;

    // Resize the output (passed by reference) matrices.
    iterm.resize(n_st3, 1);
    vep.resize(n_st3, 1);
    ve.resize(n_st3, 1);
    F_EX.resize(n_st3, 1);
    
    // Local variable for storing indices where V_E is nearly zero.
    MatrixXd ve_low(0, 1);

    // Resize several output parameters.
    exc_pot.resize(n_st3, 5);
    V_A.resize(n_st3, 1);
    V_As.resize(n_st3, 1);
    V_B.resize(n_st3, 1);
    V_R.resize(n_st3, 1);
    V_TR.resize(n_st3, 1);
    R_f.resize(n_st3, 1);
    Efd.resize(n_st3, 1);

    for (int li = 0; li < n_st3; ++li) {
        // Machine number vector

        int lj = st3_idx(li, 0) - 1;
        
        // Assign machine number using mac_int and exc_con.
        n(li, 0) = mac_int((int)exc_con(lj, 1) - 1, 0);
        
        // Get the bus number; note that bus_int is assumed to be column vector.
        n_bus(li, 0) = bus_int((int)mac_con((int)n(li, 0) - 1, 1) - 1, 0);

        // Set Efd for the corresponding machine.
        Efd((int)n(li, 0) - 1, 0) = vex((int)n(li, 0) - 1, 0);

        if (Efd((int)n(li, 0) - 1, 0) > exc_con(lj, 17)) {
            cout << "EXC_ST3: Efd exceeds maximum in initialization at " 
                << n(li, 0) - 1 << "\n";
        }
        
        // Calculate exc_pot components.
        exc_pot(lj, 0) = exc_con(lj, 12) * cos(exc_con(lj, 13) * M_PI / 180);
        exc_pot(lj, 1) = exc_con(lj, 12) * sin(exc_con(lj, 13) * M_PI / 180);

        // Compute iterm.
        iterm((int)n(li, 0) - 1, 0) = (pelect((int)n(li, 0) - 1, 0) 
            - jay * qelect((int)n(li, 0) - 1, 0)) /
            (eterm((int)n(li, 0) - 1, 0) * exp(-jay * theta((int)n_bus(lj, 0) - 1, 0))) *
            mac_pot((int)n(li, 0) - 1, 0);

        // Compute vep.
        vep((int)n(li, 0) - 1, 0) = eterm((int)n(li, 0) - 1, 0) 
            * exp(jay * theta((int)n_bus(li, 0) - 1, 0)) *
            (exc_pot(lj, 0) + jay * exc_pot(lj, 1));

        // Compute ve.
        ve((int)n(li, 0) - 1, 0) = vep((int)n(li, 0) - 1, 0) 
            + jay * (exc_con(lj, 14) +
            (exc_pot(lj, 0) + jay * exc_pot(lj, 1)) * exc_con(lj, 15))
            * iterm((int)n(li, 0) - 1, 0);

        // Calculate the magnitude.
        V_E(li, 0) = abs(ve(li, 0));

        // If the computed voltage is nearly zero, store the index.
        if (V_E(li, 0) < 1e-6) {
            int currentRows = ve_low.rows();
            ve_low.conservativeResize(currentRows + 1, NoChange);
            ve_low(currentRows, 0) = li;
        }
        
        // Compute I_N.
        I_N((int)n(li, 0) - 1, 0) = exc_con(lj, 16) * fldcur((int)n(li, 0) - 1, 0)
            / V_E((int)n(li, 0) - 1, 0);

        // Determine F_EX and update low_IN, big_IN, or mid_IN.
        if (I_N((int)n(li, 0) - 1, 0) < 0.433) {
            int currentRows = low_IN.rows();
            low_IN.conservativeResize(currentRows + 1, NoChange);
            low_IN(currentRows, 0) = n(li, 0);
            F_EX((int)n(li, 0) - 1, 0) = 1 - 0.5771 * I_N((int)n(li, 0) - 1, 0);
        } else if (I_N((int)n(li, 0) - 1, 0) > 0.75) {
            int currentRows = big_IN.rows();
            big_IN.conservativeResize(currentRows + 1, NoChange);
            big_IN(currentRows, 0) = n(li, 0);
            F_EX((int)n(li, 0) - 1, 0) = 1.708 * (1 - I_N((int)n(li, 0) - 1, 0));
        } else {
            int currentRows = mid_IN.rows();
            mid_IN.conservativeResize(currentRows + 1, NoChange);
            mid_IN(currentRows, 0) = n(li, 0);
            F_EX((int)n(li, 0) - 1, 0) = pow(0.75 * (1 - pow(I_N((int)n(li, 0) - 1, 0), 2)), 0.5);
        }
        
        if (F_EX((int)n(li, 0) - 1, 0) <= 0) {
            cout << "the F_EX(" << (int)n(li, 0) - 1 << ",0) is non-positive\n";
        }
        // Compute V_B and V_R.
        V_B(lj, 0) = V_E((int)n(li, 0) - 1, 0) * F_EX((int)n(li, 0) - 1, 0);
        V_R(lj, 0) = Efd(lj, 0) / V_B(lj, 0);

        // Ensure KA (at exc_con(lj, 3)) is nonzero.
        if (exc_con(lj, 3) == 0) {
            exc_con(lj, 3) = 1;
        }

        // Compute V_A.
        V_A(lj, 0) = V_R(lj, 0) / exc_con(lj, 3) + 
            min(exc_con(lj, 19), exc_con(lj, 18) * Efd(lj, 0));
        V_As(lj, 0) = V_A(lj, 0);
        exc_pot(lj, 4) = 1;

        
        cout << "st3_TB_idx is ; \n" << st3_TB_idx << "\n";
        cout << "TB is ; \n" << TB << "\n";

        // TB(lj, 0) = st3_TB_idx(lj, 0);  // needs checking
        // exc_pot((int)TB(lj, 0) - 1, 4) = 
        //     exc_con((int)TB(lj, 0) - 1, 6) / exc_con((int)TB(lj, 0) - 1, 5);
        
        if (TB(lj, 0) != -1) { // TB is handles poorly ... 
            // Convert TB index (assumed to be 1-based) to a 0-based index
            int idx = static_cast<int>(TB(lj, 0)) - 1;
    
            // It’s a good idea to check that idx is within the bounds of exc_con and exc_pot.
            if (idx >= 0 && idx < exc_con.rows() && idx < exc_pot.rows()) {
                // Perform the calculation only if exc_con has enough columns (i.e., at least 7) 
                // and exc_pot has at least 5 columns.
                exc_pot(idx, 4) = exc_con(idx, 6) / exc_con(idx, 5);
            }
            else {
                std::cerr << "Index " << idx << " is out of bounds!" << std::endl;
            }
        }

        // double TB_val = (lj < TB.rows()) ? TB(lj, 0) : -1;

        // if (TB_val != -1) {
        //     // Convert from 1-based to 0-based index
        //     int idx = static_cast<int>(TB_val) - 1;
    
        //     // Check that idx is within bounds of exc_con and exc_pot
        //     if (idx >= 0 && idx < exc_con.rows() && idx < exc_pot.rows()) {
        //         exc_pot(idx, 4) = exc_con(idx, 6) / exc_con(idx, 5);
        //     } else {
        //         std::cerr << "Index " << idx << " is out of bounds!" << std::endl;
        //     }
        // }
        
        V_I((int)n(li, 0) - 1, 0) = V_A(lj, 0) / exc_con(lj, 11);
        if (V_I((int)n(li, 0) - 1, 0) > exc_con(lj, 9)) {
            cout << "EXC_ST3: V_I above maximum in initialization at index " 
                 << (int)n(li, 0) - 1 << "\n";
        }
        if (V_I((int)n(li, 0) - 1, 0) < exc_con(lj, 10)) {
            cout << "EXC_ST3: V_I below minimum in initialization at index " 
                 << (int)n(li, 0) - 1 << "\n";
        }


        // Final exc_pot and other updates.
        exc_pot(lj, 2) = eterm((int)n(li, 0) - 1, 0) + V_I((int)n(li, 0) - 1, 0);
        V_TR(lj, 0) = eterm((int)n(li, 0) - 1, 0);
        R_f(lj, 0) = 0;
    }
}
