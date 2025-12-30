#include "../include/H_header.h"

using namespace std;
using namespace Eigen;


void save_maccon_matrix(ofstream &f, const MatrixXd &mac_con, const string &filename)
{
    if (!f.is_open()) {
        cerr << "File didn't open!" << endl;
        return;
    }

    int rows = mac_con.rows();
    int cols = mac_con.cols();

    // MATLAB scale array:
    vector<long long> scale = {
        (1LL<<0), (1LL<<0), (1LL<<0),
        (1LL<<12), (1LL<<12), (1LL<<12), (1LL<<12), (1LL<<12),
        (1LL<<7),  (1LL<<7),
        (1LL<<12), (1LL<<12), (1LL<<12),
        (1LL<<7),  (1LL<<7),
        (1LL<<4),
        (1LL<<7), (1LL<<7),
        (1LL<<0),
        (1LL<<7), (1LL<<7), (1LL<<7), (1LL<<7)
    };
    
    
    if (cols > (int)scale.size()) {
        cerr << "Error: columns exceed scale size (23)" << endl;
        return;
    }
    
    // Write matrix values
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            double val = mac_con(i, j);
            long long r_fixed = llround(val * scale[j]);  // fixed-point conversion

            // MATLAB code: fprintf(fid, "%d,%d,%d\n", i-1, j, r_fixed);
            f << (i - 1) << "," << (j + 0) << "," << r_fixed << "\n";
        }
    }

    // End marker
    f << "eof\n";

    // Footer comment
    f << filename << "     : row,col,real_fix(d)\n";
}


void save_macpot_matrix(ofstream &f, const MatrixXd &matrix, const string &filename)
{
    if (!f.is_open()) {
        cerr << "File didn't open!" << endl;
        return;
    }

    int rows = matrix.rows();
    int cols = matrix.cols();

    // MATLAB scale array: scale(1)=2^10, scale(2:15)=2^12
    vector<long long> scale(15);
    scale[0] = (1LL << 10);                // 2^10
    for (int k = 1; k < 15; k++)
        scale[k] = (1LL << 12);            // 2^12


    // what should be the scale size here?
    // if (cols > 15) {
    //     cerr << "Error: Columns exceed scale size (15)" << endl;
    //     return;
    // }

    // Write values
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            double val = matrix(i, j);
            long long r_fixed = llround(val * scale[j]);

            // MATLAB: fprintf(fid,"%d,%d,%d\n",i-1,j,r_fixed);
            f << (i - 1) << "," << j << "," << r_fixed << "\n";
        }
    }

    // End marker
    f << "//eof\n";

    // Footer comment (same as MATLAB)
    f << filename << "    // : row,col,real_fix(d),imag_fix(d)\n";
}
