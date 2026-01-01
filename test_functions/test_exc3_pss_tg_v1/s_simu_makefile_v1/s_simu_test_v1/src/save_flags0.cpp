#include "../include/H_header.h"

using namespace std;
using namespace Eigen;


void save_maccon_matrix(ofstream &f,
                        const Eigen::MatrixXd &matrix,
                        const std::string &filename)
{
    if (!f.is_open()) {
        std::cerr << "File didn't open!" << std::endl;
        return;
    }

    int rows = matrix.rows();
    int cols = matrix.cols();

    // MATLAB scale array (23 elements)
    std::vector<long long> scale = {
        (1LL<<0), (1LL<<0), (1LL<<0),
        (1LL<<12), (1LL<<12), (1LL<<12),
        (1LL<<12), (1LL<<12),
        (1LL<<7),  (1LL<<7),
        (1LL<<12), (1LL<<12), (1LL<<12),
        (1LL<<7),  (1LL<<7),
        (1LL<<4),
        (1LL<<7),  (1LL<<7),
        (1LL<<0),
        (1LL<<7),  (1LL<<7),
        (1LL<<7),  (1LL<<7)
    };

    // if (cols > (int)scale.size()) {
    //     std::cerr << "Error: columns exceed scale size (23)" << std::endl;
    //     return;
    // }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            double val = matrix(i, j);
            long long r_fixed = llround(val * scale[j]);

            // MATLAB intended:
            // fprintf(fid,'%d,%d,%d\n', i-1, j, r_fixed);
            f << (i - 1) << ","
              << j << ","
              << r_fixed << "\n";
        }
    }

    // End marker
    f << "eof\n";

    // Footer comment
    f << filename
      << "     : row,col,real_fix(d)\n";
}


void save_macpot_matrix(std::ofstream &f,
                        const Eigen::MatrixXd &matrix,
                        const std::string &filename)
{
    if (!f.is_open()) {
        std::cerr << "File didn't open!" << std::endl;
        return;
    }

    int rows = matrix.rows();
    int cols = matrix.cols();

    // MATLAB scale:
    // scale(1) = 2^10
    // scale(2:15) = 2^12
    std::vector<long long> scale(15);
    scale[0] = (1LL << 10);
    for (int k = 1; k < 15; ++k)
        scale[k] = (1LL << 12);

    // if (cols > (int)scale.size()) {
    //     std::cerr << "Error: columns exceed scale size (15)" << std::endl;
    //     return;
    // }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {

            double val = matrix(i, j);
            long long r_fixed = llround(val * scale[j]);

            // MATLAB intended:
            // fprintf(fid,'%d,%d,%d\n', i-1, j, r_fixed);
            f << (i - 1) << ","
              << j << ","
              << r_fixed << "\n";
        }
    }

    // End marker
    f << "//eof\n";

    // Footer comment
    f << filename
      << "    // : row,col,real_fix(d)\n";
}


void save_psscon_matrix(std::ofstream &f,
                        const Eigen::MatrixXd &pss_con,
                        const Eigen::MatrixXd &matrix,
                        const std::string &filename)
{
    if (!f.is_open()) {
        std::cerr << "File didn't open!" << std::endl;
        return;
    }

    int rows = matrix.rows();
    int cols = matrix.cols();

    // MATLAB scale array:
    // scale(1:10) = [2^0 2^0 2^0 2^4 2^7 2^7 2^7 2^7 2^7 2^7]
    std::vector<long long> scale = {
        (1LL << 0), (1LL << 0), (1LL << 0),
        (1LL << 4),
        (1LL << 7), (1LL << 7), (1LL << 7),
        (1LL << 7), (1LL << 7), (1LL << 7)
    };

    if (cols > (int)scale.size()) {
        std::cerr << "Error: columns exceed scale size (10)" << std::endl;
        return;
    }

    for (int i = 0; i < rows; ++i) {

        // MATLAB:
        // mac_num = pss_con(i,2);
        // mac_index = mac_num - 1;
        int mac_num   = static_cast<int>(pss_con(i, 1));
        int mac_index = mac_num - 1;

        for (int j = 0; j < cols; ++j) {

            double val = matrix(i, j);
            long long r_fixed = llround(val * scale[j]);

            // MATLAB:
            // fprintf(fid,'%d,%d,%d,%d\n', mac_index, i-1, j, r_fixed);
            f << mac_index << ","
              << (i - 1) << ","
              << j << ","
              << r_fixed << "\n";
        }
    }

    // End marker
    f << "//eof\n";

    // Footer comment
    f << filename
      << "    // pss_con: mac_index, row,col,real_fix(d)\n";
}



void save_psspot_matrix(std::ofstream &f,
                        const Eigen::MatrixXd &matrix,
                        const Eigen::MatrixXd &pss_con,
                        const std::string &filename)
{
    if (!f.is_open()) {
        std::cerr << "File didn't open!" << std::endl;
        return;
    }

    // MATLAB: if ~isempty(pss_con)
    if (pss_con.size() == 0) {
        return;
    }

    int rows = matrix.rows();
    int cols = matrix.cols();

    // MATLAB scale:
    // scale(1:2) = [2^7 2^7]
    std::vector<long long> scale = {
        (1LL << 7),
        (1LL << 7)
    };

    if (cols > (int)scale.size()) {
        std::cerr << "Error: columns exceed scale size (2)" << std::endl;
        return;
    }

    for (int i = 0; i < rows; ++i) {

        // MATLAB:
        // mac_num   = pss_con(i,2);
        // mac_index = mac_num - 1;
        int mac_num   = static_cast<int>(pss_con(i, 1));
        int mac_index = mac_num - 1;

        for (int j = 0; j < cols; ++j) {

            double val = matrix(i, j);
            long long r_fixed = llround(val * scale[j]);

            // MATLAB:
            // fprintf(fid,'%d,%d,%d,%d\n', mac_index, i-1, j, r_fixed);
            f << mac_index << ","
              << (i - 1) << ","
              << j << ","
              << r_fixed << "\n";
        }
    }

    // End marker
    f << "//eof\n";

    // Footer comment
    f << filename
      << "    // pss_pot: mac_index, row,col,real_fix(d)\n";
}


void save_tgcon_matrix(std::ofstream &f,
                       const Eigen::MatrixXd &matrix,
                       const Eigen::MatrixXd &tg_con,
                       const std::string &filename)
{
    if (!f.is_open()) {
        std::cerr << "File didn't open!" << std::endl;
        return;
    }

    int rows = matrix.rows();
    int cols = matrix.cols();

    // MATLAB scale:
    // scale(1:10) = [2^0 2^0 2^12 2^0 2^7 2^4 2^4 2^4 2^4 2^4]
    std::vector<long long> scale = {
        (1LL << 0),   // col 1
        (1LL << 0),   // col 2
        (1LL << 12),  // col 3
        (1LL << 0),   // col 4
        (1LL << 7),   // col 5
        (1LL << 4),   // col 6
        (1LL << 4),   // col 7
        (1LL << 4),   // col 8
        (1LL << 4),   // col 9
        (1LL << 4)    // col10
    };

    if (cols > (int)scale.size()) {
        std::cerr << "Error: columns exceed scale size (10)" << std::endl;
        return;
    }

    for (int i = 0; i < rows; ++i) {

        // MATLAB:
        // mac_num   = tg_con(i,2);
        // mac_index = mac_num - 1;
        int mac_num   = static_cast<int>(tg_con(i, 1));
        int mac_index = mac_num - 1;

        for (int j = 0; j < cols; ++j) {

            double val = matrix(i, j);
            long long r_fixed = llround(val * scale[j]);

            // MATLAB:
            // fprintf(fid,'%d,%d,%d,%d\n', mac_index, i-1, j, r_fixed);
            f << mac_index << ","
              << (i - 1) << ","
              << j << ","
              << r_fixed << "\n";
        }
    }

    // End marker
    f << "//eof\n";

    // Footer comment
    f << filename
      << "    // tg_pot: mac_index, row,col,real_fix(d)\n";
}


void save_tgpot_matrix(std::ofstream &f,
                       const Eigen::MatrixXd &matrix,
                       const Eigen::MatrixXd &tg_con,
                       const std::string &filename)
{
    if (!f.is_open()) {
        std::cerr << "File didn't open!" << std::endl;
        return;
    }

    int rows = matrix.rows();
    int cols = matrix.cols();

    // MATLAB scale:
    // scale(1:5) = 2^12
    std::vector<long long> scale(5, (1LL << 12));

    if (cols > (int)scale.size()) {
        std::cerr << "Error: columns exceed scale size (5)" << std::endl;
        return;
    }

    for (int i = 0; i < rows; ++i) {

        // MATLAB:
        // mac_num   = tg_con(i,2);
        // mac_index = mac_num - 1;
        int mac_num   = static_cast<int>(tg_con(i, 1));
        int mac_index = mac_num - 1;

        for (int j = 0; j < cols; ++j) {

            double val = matrix(i, j);
            long long r_fixed = llround(val * scale[j]);

            // MATLAB:
            // fprintf(fid,'%d,%d,%d,%d\n', mac_index, i-1, j, r_fixed);
            f << mac_index << ","
              << (i - 1) << ","
              << j << ","
              << r_fixed << "\n";
        }
    }

    // End marker
    f << "//eof\n";

    // Footer comment
    f << filename
      << "    // tg_pot: mac_index, row,col,real_fix(d)\n";
}

void save_exccon_matrix(std::ofstream &f,
                        const Eigen::MatrixXd &matrix,
                        const Eigen::MatrixXd &exc_con,
                        const std::string &filename)
{
    if (!f.is_open()) {
        std::cerr << "File didn't open!" << std::endl;
        return;
    }

    int rows = matrix.rows();
    int cols = matrix.cols();

    // MATLAB scale:
    // scale(1:20) = [2^0,2^0,2^10,2^0,2^10,2^7,2^7,2^4,2^4,
    //                2^7,2^7,2^4,2^4,2^4,2^4,2^7,2^7,2^7,2^7,2^7]
    std::vector<long long> scale = {
        (1LL << 0),  (1LL << 0),  (1LL << 10), (1LL << 0),  (1LL << 10),
        (1LL << 7),  (1LL << 7),  (1LL << 4),  (1LL << 4),
        (1LL << 7),  (1LL << 7),  (1LL << 4),  (1LL << 4),
        (1LL << 4),  (1LL << 4),
        (1LL << 7),  (1LL << 7),  (1LL << 7),  (1LL << 7),  (1LL << 7)
    };

    if (cols > (int)scale.size()) {
        std::cerr << "Error: columns exceed scale size (20)" << std::endl;
        return;
    }

    for (int i = 0; i < rows; ++i) {

        // MATLAB:
        // mac_num   = exc_con(i,2);
        // mac_index = mac_num - 1;
        int mac_num   = static_cast<int>(exc_con(i, 1));
        int mac_index = mac_num - 1;

        for (int j = 0; j < cols; ++j) {

            double val = matrix(i, j);
            long long r_fixed = llround(val * scale[j]);

            // MATLAB:
            // fprintf(fid,'%d,%d,%d,%d\n', mac_index, i-1, j, r_fixed);
            f << mac_index << ","
              << (i - 1) << ","
              << j << ","
              << r_fixed << "\n";
        }
    }

    // End marker
    f << "//eof\n";

    // Footer comment
    f << filename
      << "    // exc_con: mac_index , row,col,real_fix(d)\n";
}

void save_excpot_matrix(std::ofstream &f,
                        const Eigen::MatrixXd &matrix,
                        const Eigen::MatrixXd &exc_con,
                        const std::string &filename)
{
    if (!f.is_open()) {
        std::cerr << "File didn't open!" << std::endl;
        return;
    }

    int rows = matrix.rows();
    int cols = matrix.cols();

    // MATLAB scale:
    // scale(1:5) = [2^7, 2^7, 2^16, 2^7, 2^7]
    std::vector<long long> scale = {
        (1LL << 7),
        (1LL << 7),
        (1LL << 16),
        (1LL << 7),
        (1LL << 7)
    };

    if (cols > (int)scale.size()) {
        std::cerr << "Error: columns exceed scale size (5)" << std::endl;
        return;
    }

    for (int i = 0; i < rows; ++i) {

        // MATLAB:
        // mac_num   = exc_con(i,2);
        // mac_index = mac_num - 1;
        int mac_num   = static_cast<int>(exc_con(i, 1));
        int mac_index = mac_num - 1;

        for (int j = 0; j < cols; ++j) {

            double val = matrix(i, j);
            long long r_fixed = llround(val * scale[j]);

            // FIXED format (comma-separated)
            // MATLAB intended:
            // fprintf(fid,'%d,%d,%d,%d\n', mac_index, i-1, j, r_fixed);
            f << mac_index << ","
              << (i - 1) << ","
              << j << ","
              << r_fixed << "\n";
        }
    }

    // End marker
    f << "//eof\n";

    // Footer comment
    f << filename
      << "    // exc_pot: mac_index , row,col,real_fix(d)\n";
}


void save_exc_coefficient(std::ofstream &f,
                          const Eigen::MatrixXd &exc_con,
                          const Eigen::MatrixXd &exc_pot,
                          const std::string &filename)
{
    if (!f.is_open()) {
        std::cerr << "File didn't open!" << std::endl;
        return;
    }

    int n = exc_pot.rows();

    // Header (MATLAB prints this)
    f << "% machine_id  exc_vep_coef_mag  exc_vep_coef_phase  "
         "exc_ve_coef_mag  exc_ve_coef_phase\n";

    // Fixed-point scales
    const double mag_scale       = std::pow(2.0, 7);
    const double phase_scale     = std::pow(2.0, 12);
    const double mag_scale_ve    = std::pow(2.0, 16);
    const double phase_scale_ve  = std::pow(2.0, 12);

    for (int i = 0; i < n; ++i) {

        // MATLAB: machine_id = exc_con(i,2)
        // Consistent with other exporters → index starts from 0
        int machine_id = static_cast<int>(exc_con(i, 1)) - 1;

        // exc_vep = exc_pot(i,1) + j*exc_pot(i,2)
        std::complex<double> exc_vep(
            exc_pot(i, 0),
            exc_pot(i, 1)
        );

        double exc_vep_mag   = std::abs(exc_vep);
        double exc_vep_phase = std::arg(exc_vep);

        long long exc_vep_mag_fix =
            llround(exc_vep_mag * mag_scale);
        long long exc_vep_phase_fix =
            llround(exc_vep_phase * phase_scale);

        // tmp = exc_con(i,15) + exc_con(i,16) * exc_vep
        std::complex<double> tmp =
            exc_con(i, 14) + exc_con(i, 15) * exc_vep;

        // exc_ve = j * tmp
        std::complex<double> exc_ve(0.0, 1.0);
        exc_ve *= tmp;

        double exc_ve_mag   = std::abs(exc_ve);
        double exc_ve_phase = std::arg(exc_ve);

        long long exc_ve_mag_fix =
            llround(exc_ve_mag * mag_scale_ve);
        long long exc_ve_phase_fix =
            llround(exc_ve_phase * phase_scale_ve);

        // ONE LINE OUTPUT (fixed & consistent)
        f << machine_id << "  "
          << exc_vep_mag_fix << "  "
          << exc_vep_phase_fix << "  "
          << exc_ve_mag_fix << "  "
          << exc_ve_phase_fix << "\n";
    }
}


void save_Flag0_mac_variables(std::ofstream &f,
                              const std::string &filename,
                              const Eigen::VectorXd &mac_ang,
                              const Eigen::VectorXd &edprime,
                              const Eigen::VectorXd &eqprime,
                              const Eigen::VectorXd &psikd,
                              const Eigen::VectorXd &psikq,
                              const Eigen::VectorXd &vex,
                              const Eigen::VectorXd &pmech,
                              const Eigen::VectorXd &pelec)
{
    if (!f.is_open()) {
        std::cerr << "Cannot open file." << std::endl;
        return;
    }

    // Helper structure (name + data)
    struct Var {
        std::string name;
        const Eigen::VectorXd &data;
    };

    std::vector<Var> vars = {
        {"mac_ang",  mac_ang},
        {"edprime",  edprime},
        {"eqprime",  eqprime},
        {"psikd",    psikd},
        {"psikq",    psikq},
        {"vex",      vex},
        {"pmech",    pmech},
        {"pelec",    pelec}
    };

    f << std::fixed << std::setprecision(15);

    for (const auto &v : vars) {

        // MATLAB: fprintf(fid, "//%s\n", name);
        f << "//" << v.name << "\n";

        // MATLAB: for i = 1:4
        for (int i = 0; i < 4; ++i) {

            // MATLAB:
            // fprintf(fid,"%s[%d] = %.15f;\n", name, i-1, M(i,1));
            f << v.name << "[" << i << "] = "
              << v.data(i) << ";\n";
        }

        f << "\n";
    }
}
