#include "../include/H_header.h"

using namespace std;
using namespace Eigen;

// ----------------------------------------------------------------------
// Write a simple real vector (Nx1) using 1-based indexing
// ----------------------------------------------------------------------
void writeRealVector(ofstream &f, const string &name, const MatrixXd &v)
{
    f << "// " << name << "\n";
    for (int i = 0; i < v.rows(); ++i)
    {
        double val = v(i, 0);
        if (!std::isnan(val))
        {
            f << name << "[" << (i + 1) << "] = "
              << std::setprecision(15) << val << ";\n";
        }
    }
    f << "\n";
}

// ----------------------------------------------------------------------
// Write complex vector (Nx1) as real + imag using 1-based indexing
// ----------------------------------------------------------------------
void writeComplexVector(ofstream &f, const string &name, const MatrixXcd &v)
{
    f << "// " << name << " (real part)\n";
    for (int i = 0; i < v.rows(); ++i)
    {
        double re = v(i, 0).real();
        if (!std::isnan(re))
        {
            f << name << "_re[" << (i + 1) << "] = "
              << std::setprecision(15) << re << ";\n";
        }
    }
    f << "\n";

    f << "// " << name << " (imag part)\n";
    for (int i = 0; i < v.rows(); ++i)
    {
        double im = v(i, 0).imag();
        if (!std::isnan(im))
        {
            f << name << "_im[" << (i + 1) << "] = "
              << std::setprecision(15) << im << ";\n";
        }
    }
    f << "\n";
}

// ----------------------------------------------------------------------
// Write REAL vector using ACTUAL MACHINE INDEX (1-based)
// ----------------------------------------------------------------------
void writeIndexedRealVector(ofstream &f,
                            const string &name,
                            const MatrixXd &values,
                            const MatrixXd &machine_idx)
{
    f << "// " << name << " (indexed by machine number)\n";

    for (int r = 0; r < values.rows(); ++r)
    {
        double val  = values(r, 0);
        int mach_id = machine_idx(r, 0);  // MATLAB 1-based

        f << name << "[" << mach_id << "] = "
          << std::setprecision(15) << val << ";\n";
    }

    f << "\n";
}

// ----------------------------------------------------------------------
// Write COMPLEX vector using ACTUAL MACHINE INDEX (1-based)
// ----------------------------------------------------------------------
void writeIndexedComplexVector(ofstream &f,
                               const string &name,
                               const MatrixXcd &values,
                               const MatrixXd &machine_idx)
{
    f << "// " << name << " (real part, indexed by machine)\n";
    for (int r = 0; r < values.rows(); ++r)
    {
        int mach_id = machine_idx(r, 0);
        double re = values(r, 0).real();

        f << name << "_re[" << mach_id << "] = "
          << std::setprecision(15) << re << ";\n";
    }
    f << "\n";

    f << "// " << name << " (imag part, indexed by machine)\n";
    for (int r = 0; r < values.rows(); ++r)
    {
        int mach_id = machine_idx(r, 0);
        double im = values(r, 0).imag();

        f << name << "_im[" << mach_id << "] = "
          << std::setprecision(15) << im << ";\n";
    }
    f << "\n";
}



// ===================================================================
// SAVE EXC_ST3 OUTPUTS (NOW CORRECTLY USING st3_idx!)
// ===================================================================
void save_exc_st3_outputs(
    const string &filename,
    const MatrixXcd &iterm,
    const MatrixXcd &vep,
    const MatrixXcd &ve,
    const MatrixXd &F_EX,
    const MatrixXd &Efd,
    const MatrixXd &V_B,
    const MatrixXd &V_R,
    const MatrixXd &V_A,
    const MatrixXd &V_As,
    const MatrixXd &V_TR,
    const MatrixXd &R_f,
    const MatrixXd &V_I,
    const MatrixXd &V_E,
    const MatrixXd &I_N,
    const MatrixXd &low_IN,
    const MatrixXd &n_bus_mat,
    const MatrixXd &n_mat,
    const MatrixXd &st3_idx     // ⭐ machine index matrix
)
{
    ofstream f(filename);
    if (!f.is_open()) { cerr << "Cannot open file: " << filename << "\n"; return; }

    // ⭐ Complex values mapped to machine numbers
    writeIndexedComplexVector(f, "iterm", iterm, st3_idx);
    writeIndexedComplexVector(f, "vep",   vep,   st3_idx);
    writeIndexedComplexVector(f, "ve",    ve,    st3_idx);

    // ⭐ Real values mapped to machine numbers
    writeIndexedRealVector(f, "F_EX", F_EX, st3_idx);
    writeIndexedRealVector(f, "Efd",  Efd,  st3_idx);
    writeIndexedRealVector(f, "V_B",  V_B,  st3_idx);
    writeIndexedRealVector(f, "V_R",  V_R,  st3_idx);
    writeIndexedRealVector(f, "V_A",  V_A,  st3_idx);
    writeIndexedRealVector(f, "V_As", V_As, st3_idx);
    writeIndexedRealVector(f, "V_TR", V_TR, st3_idx);
    writeIndexedRealVector(f, "R_f",  R_f,  st3_idx);
    writeIndexedRealVector(f, "V_I",  V_I,  st3_idx);
    writeIndexedRealVector(f, "V_E",  V_E,  st3_idx);
    writeIndexedRealVector(f, "I_N",  I_N,  st3_idx);

    // These remain sequential (not machine-specific)
    writeRealVector(f, "low_IN",  low_IN);
    writeRealVector(f, "n_bus",   n_bus_mat);
    writeRealVector(f, "n",       n_mat);

    f.close();
}



// ===================================================================
// SAVE TG OUTPUTS (ALREADY FIXED)
// ===================================================================
void save_tg_outputs(
    const string &filename,
    const MatrixXd &tg1,
    const MatrixXd &tg2,
    const MatrixXd &tg3,
    const MatrixXd &tg_pot,
    const MatrixXd &tg_sig,
    const MatrixXd &n_tg_mat     // machine numbers
)
{
    ofstream f(filename);
    if (!f.is_open()) { cerr << "Cannot open file: " << filename << "\n"; return; }

    writeIndexedRealVector(f, "tg1", tg1, n_tg_mat);
    writeIndexedRealVector(f, "tg2", tg2, n_tg_mat);
    writeIndexedRealVector(f, "tg3", tg3, n_tg_mat);
    writeIndexedRealVector(f, "tg_sig", tg_sig, n_tg_mat);

    // write tg_pot as rows (not indexed by machine)
    f << "// tg_pot (rows × cols)\n";
    for (int r = 0; r < tg_pot.rows(); ++r)
    {
        f << "tg_pot_row" << (r + 1) << " = { ";
        for (int c = 0; c < tg_pot.cols(); ++c)
        {
            f << tg_pot(r, c);
            if (c < tg_pot.cols() - 1) f << ", ";
        }
        f << " };\n";
    }
    f << "\n";

    f.close();
}
