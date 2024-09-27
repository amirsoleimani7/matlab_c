#include <iostream>
#include <eigen3/Eigen/Core>
#include <complex>

using namespace Eigen;
using namespace std;

MatrixXcd  Division_Two_Matrix(MatrixXcd A, MatrixXcd B)
{
    // MatrixXcd B_inv = B.array().inverse();
    // cout << "A is \n" << A << "\n";
    // cout << "B_inv \n" << B_inv << "\n";
    cout << A.rows() << " " << A.cols() << "\n";
    cout << B.rows() << " " << B.cols() << "\n";


    MatrixXcd result(13 ,13);
    // cout << "resuld \n" << result << "\n";
    for(int i =0;i<13;++i ){
        for(int j= 0 ;j<13;++j){

            if (B(i, j) != std::complex<double>(0, 0)) {
                result(i, j) = A(i, j) / B(i, j);
            } else {
                result(i, j) = std::complex<double>(0, 0); // or some other value depending on the context
            }
                
        }
    }

    // for(int i = 0;i<A.array().size();++i){

    //     result(i) = A(i) / B(i);
    // }
    return result;
}

int main() {
    // Define two 2x2 complex matrices
    MatrixXcd A(2, 2);
    MatrixXcd B(2, 2);

    // Initialize the matrices
    A << std::complex<double>(1, 2), std::complex<double>(3, 4),
         std::complex<double>(5, 6), std::complex<double>(7, 8);
    
    B << std::complex<double>(1, -1), std::complex<double>(2, -2),
         std::complex<double>(-1, 1), std::complex<double>(-2, 2);

    // Perform matrix division
    // Output the result
    std::cout << "Matrix C:\n" << C << std::endl;

    return 0;
}
