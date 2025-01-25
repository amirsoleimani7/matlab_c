#include "H_header.h"

using namespace Eigen;
using namespace std;

void exc_st3_initialization(
    const MatrixXd &exc_con, const MatrixXd &mac_con, const MatrixXd &bus_int, 
    const MatrixXd &mac_int, const MatrixXd &vex, const MatrixXd &pelect, 
    const MatrixXd &qelect, const MatrixXd &eterm, const MatrixXd &theta, 
    const MatrixXd &fldcur, MatrixXd &Efd, MatrixXd &exc_pot, 
    MatrixXd &V_B, MatrixXd &V_R, MatrixXd &V_A, MatrixXd &V_As, 
    MatrixXd &V_TR, MatrixXd &R_f, const MatrixXd &st3_idx, 
    const MatrixXd &st3_TB_idx)

{

    const std::complex<double> jay(0, 1); // this is the jay (sqrt(-1))
    int n_st3 = st3_idx.rows();
    MatrixXd V_E = MatrixXd::Zero(n_st3, 1);
    MatrixXd I_N = V_E;
    MatrixXd iterm = V_E;
    MatrixXd vep = V_E;
    MatrixXd ve = V_E;
    MatrixXd F_EX = V_E;

    // Machine number vector
    MatrixXd n = mac_int(exc_con(st3_idx.array().cast<int>(), 1).array().cast<int>());

    // Generator bus number vector
    MatrixXd n_bus = bus_int(mac_con(n.array().cast<int>(), 1).array().cast<int>());

    // Initialize Efd
    Efd(st3_idx.array().cast<int>(), 0) = vex(n.array().cast<int>(), 0);

    // Check maximum limit
    MatrixXd max_lim = (Efd(st3_idx.array().cast<int>(), 0).array() > exc_con(st3_idx.array().cast<int>(), 17).array()).cast<double>();
    if (max_lim.sum() > 0) {
        std::cerr << "EXC_ST3: Efd exceeds maximum in initialization." << std::endl;
        MatrixXd n_error = mac_int(exc_con(max_lim.cast<int>(), 1).array().cast<int>(), 0);
        throw std::runtime_error("Initialization error: Efd exceeds maximum.");
    }

    exc_pot(st3_idx.array().cast<int>(), 0) = exc_con(st3_idx.array().cast<int>(), 12).array() * cos(exc_con(st3_idx.array().cast<int>(), 13).array() * M_PI / 180.0);
    exc_pot(st3_idx.array().cast<int>(), 1) = exc_con(st3_idx.array().cast<int>(), 12).array() * sin(exc_con(st3_idx.array().cast<int>(), 13).array() * M_PI / 180.0);

    // Calculate intermediate variables
    iterm = (pelect(n.array().cast<int>(), 0) - jay * qelect(n.array().cast<int>(), 0)).array() /
            (eterm(n.array().cast<int>(), 0).array() * (-jay * theta(n_bus.array().cast<int>(), 0).array()).exp()).array() *
            mac_con(n.array().cast<int>(), 0).array();

    vep = eterm(n.array().cast<int>(), 0).array() * (-jay * theta(n.array().cast<int>(), 0).array()).exp().array() *
          (exc_pot(st3_idx.array().cast<int>(), 0).array() + jay * exc_pot(st3_idx.array().cast<int>(), 1).array());

    ve = vep + jay * (exc_con(st3_idx.array().cast<int>(), 14).array() +
          (exc_pot(st3_idx.array().cast<int>(), 0).array() + jay * exc_pot(st3_idx.array().cast<int>(), 1).array()).array() *
          exc_con(st3_idx.array().cast<int>(), 15).array()).array() * iterm.array();

    V_E = ve.cwiseAbs();

    // Check low voltage
    MatrixXd ve_low = (V_E.array() < 1e-6).cast<double>();
    if (ve_low.sum() > 0) {
        std::cerr << "Excitation system error: no supply voltage at the following generators." << std::endl;
        MatrixXd n_excerr = n(ve_low.cast<int>(), 0);
        throw std::runtime_error("Initialization error: no supply voltage.");
    }

    I_N = exc_con(st3_idx.array().cast<int>(), 16).array() * fldcur(n.array().cast<int>(), 0).array() / V_E.array();

    // Select operating point on the rectifier regulation characteristic
    MatrixXd low_IN = (I_N.array() < 0.433).cast<double>();
    if (low_IN.sum() > 0) {
        F_EX(low_IN.cast<int>(), 0) = MatrixXd::Ones(low_IN.sum(), 1) - 0.5771 * I_N(low_IN.cast<int>(), 0).array();
    }

    MatrixXd big_IN = (I_N.array() > 0.75).cast<double>();
    if (big_IN.sum() > 0) {
        F_EX(big_IN.cast<int>(), 0) = 1.708 * (MatrixXd::Ones(big_IN.sum(), 1) - I_N(big_IN.cast<int>(), 0).array());
    }

    MatrixXd mid_IN = ((I_N.array() > 0.433) && (I_N.array() < 0.75)).cast<double>();
    if (mid_IN.sum() > 0) {
        F_EX(mid_IN.cast<int>(), 0) = (0.75 * MatrixXd::Ones(mid_IN.sum(), 1) - I_N(mid_IN.cast<int>(), 0).array().pow(0.2)).array().sqrt();
    }

    MatrixXd fex_error = (F_EX.array() <= 0).cast<double>();
    if (fex_error.sum() > 0) {
        std::cerr << "Error: F_EX zero or negative at the following generators." << std::endl;
        MatrixXd n_error = n(fex_error.cast<int>(), 0);
        throw std::runtime_error("Initialization error: F_EX <= 0.");
    }

    V_B(st3_idx.array().cast<int>(), 0) = V_E.array() * F_EX.array();
    V_R(st3_idx.array().cast<int>(), 0) = Efd(st3_idx.array().cast<int>(), 0).array() / V_B.array();

    // Handle cases with KA = 0
    MatrixXd nKA_idx = (exc_con(st3_idx.array().cast<int>(), 3).array() == 0).cast<double>();
    if (nKA_idx.sum() > 0) {
        exc_con(st3_idx(nKA_idx.cast<int>(), 3)) = MatrixXd::Ones(nKA_idx.sum(), 1);
    }

    V_A(st3_idx.array().cast<int>(), 0) = V_R(st3_idx.array().cast<int>(), 0).array() / exc_con(st3_idx.array().cast<int>(), 3).array() +
                                           exc_con(st3_idx.array().cast<int>(), 19).array().cwiseMin(exc_con(st3_idx.array().cast<int>(), 18).array() * Efd(st3_idx.array().cast<int>(), 0).array());

    V_As(st3_idx.array().cast<int>(), 0) = V_A(st3_idx.array().cast<int>(), 0);
    exc_pot(st3_idx.array().cast<int>(), 4) = MatrixXd::Ones(n_st3, 1);

    // Update TB values
    if (st3_TB_idx.rows() > 0) {
        exc_pot(st3_idx(st3_TB_idx.array().cast<int>(), 4)) = exc_con(st3_idx(st3_TB_idx.array().cast<int>(), 6)).array() / exc_con(st3_idx(st3_TB_idx.array().cast<int>(), 5)).array();
    }

    MatrixXd V_I = V_A(st3_idx.array().cast<int>(), 0).array() / exc_con(st3_idx.array().cast<int>(), 11).array();

    MatrixXd max_VI = (V_I.array() > exc_con(st3_idx.array().cast<int>(), 9).array()).cast<double>();
    if (max_VI.sum() > 0) {
        std::cerr << "EXC_ST3: V_I above maximum in initialization." << std::endl;
        MatrixXd n_error = mac_int(exc_con(max_VI.cast<int>(), 1).array().cast<int>(), 0);
        throw std::runtime_error("Initialization error: V_I above maximum.");
    }

    MatrixXd min_VI = (V_I.array() < exc_con(st3_idx.array().cast<int>(), 10).array()).cast<double>();
    if (min_VI.sum() > 0) {
        std::cerr << "EXC_ST3: V_I below minimum in initialization." << std::endl;
        MatrixXd n_error = mac_int(exc_con(min_VI.cast<int>(), 1).array().cast<int>(), 0);
        throw std::runtime_error("Initialization error: V_I below minimum.");
    }

    exc_pot(st3_idx.array().cast<int>(), 2) = eterm(n.array().cast<int>(), 0).array() + V_I.array();
    V_TR(st3_idx.array().cast<int>(), 0) = eterm(n.array().cast<int>(), 0);
    R_f(st3_idx.array().cast<int>(), 0) = MatrixXd::Zero(n_st3, 1);
}
