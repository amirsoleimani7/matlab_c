#include <iostream>
#include <complex>
#include <eigen3/Eigen/Core>


using namespace Eigen;
using namespace std;

MatrixXcd Division_Two_Matrix(MatrixXcd A, MatrixXcd B)
{
    std::complex<double> det = B.determinant();

    if (det != complex<double>(0.0,0.0)) {
        MatrixXcd B_inv = B.array().inverse();
        MatrixXcd result = A * B_inv;
        return result;
    }
    else
    {
        return MatrixXcd::Zero(A.rows(), A.cols());
    }
}

int main()
{
    // Example usage
    MatrixXcd A(2, 2);
    MatrixXcd B(2, 2);

    A << std::complex<double>(1.0, 2.0), std::complex<double>(3.0, 4.0),
         std::complex<double>(5.0, 6.0), std::complex<double>(7.0, 8.0);

    B << std::complex<double>(2.0, 1.0), std::complex<double>(0.0, 0.0),
         std::complex<double>(1.0, 2.0), std::complex<double>(1.0, 1.0);

    MatrixXcd result = Division_Two_Matrix(A, B);

    cout << "Result is \n" << result << "\n";

    return 0;
}
