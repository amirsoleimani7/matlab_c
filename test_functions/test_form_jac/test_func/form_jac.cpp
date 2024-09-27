#include <iostream>
#include <vector>
#include <string>
#include <eigen3/Eigen/Core>


using namespace Eigen;
using namespace std;


MatrixXcd Division_Two_Matrix(MatrixXcd A, MatrixXcd B)
{
    MatrixXcd result(A.rows(), A.cols());

    for(int j = 0; j < A.cols(); ++j) {
        std::complex<double> divisor = B(j, j);

        if (divisor != std::complex<double>(0, 0)) {
            for(int i = 0; i < A.rows(); ++i) {
                result(i, j) = A(i, j) / divisor;
            }
        } else {
            for(int i = 0; i < A.rows(); ++i) {
                result(i, j) = std::complex<double>(0, 0); 
            }
        }
    }
    
    return result;
}


MatrixXcd Form_Jac_1(MatrixXd V, MatrixXd ang, MatrixXcd Y, MatrixXd ang_red, MatrixXd volt_red)
{


    complex<double> jay(0.0, 1.0);


    MatrixXcd ang_complex = (ang.array() *jay).exp();
    MatrixXcd V_rect = V.array() * ang_complex.array();
    
    cout << "V_rect is \n" << V_rect << "\n";

    MatrixXcd CV_rect = V_rect.conjugate();
    
    MatrixXcd Y_con = Y.conjugate();

    MatrixXcd i_c = Y_con * CV_rect;


    MatrixXcd inner_of_vRect_iC = V_rect.array() * i_c.array();

    MatrixXcd S = inner_of_vRect_iC.asDiagonal();


    MatrixXcd Vdia = V_rect.asDiagonal();

    MatrixXcd CVdia = Vdia.conjugate();


    MatrixXcd S1 = (Vdia * Y_con) * CVdia;

    MatrixXcd Vmag = V.asDiagonal();

    MatrixXcd sum_S_S1 = S + S1;

    MatrixXcd minus_S_S1 = S - S1;


    // Ensure Division_Two_Matrix operates on the correct types
    MatrixXcd t1 = Division_Two_Matrix(sum_S_S1, Vmag) * volt_red.transpose();
    MatrixXcd t2 = minus_S_S1* ang_red.transpose();


    MatrixXcd jac11 = (ang_red *(-1.0)) * t2.imag();

    cout << "jac11 is \n" << jac11 << "\n";

    MatrixXcd jac12 = ang_red * t1.real();
    cout << "jac12 is \n" << jac12 << "\n";

    MatrixXcd jac21 = volt_red * t2.real();

    cout << "jac21 is \n" << jac21 << "\n";

    MatrixXcd jac22 = volt_red * t1.imag();
    cout << "jac22 is \n" << jac22 << "\n";

    
    MatrixXcd Jac(jac11.rows() + jac21.rows(), jac11.cols() + jac12.cols());
    Jac <<  jac11, jac12,
            jac21, jac22;

    return Jac;
}
