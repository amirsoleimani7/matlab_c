#include "../include/H_header.h"


using namespace Eigen;
using namespace std;





MatrixXd Form_Jac_1(MatrixXd V, MatrixXd ang, MatrixXcd Y, MatrixXd ang_red, MatrixXd volt_red)
{
    cout <<"\n---in form_jac---\n";
    complex<double> jay(0.0, 1.0);

    MatrixXcd ang_complex = (ang.array() *jay).exp();
    MatrixXcd V_rect = V.array() * ang_complex.array();


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


    MatrixXd jac11 = (ang_red *(-1.0)) * t2.imag();

    MatrixXd jac12 = ang_red * t1.real();

    MatrixXd jac21 = volt_red * t2.real();

    MatrixXd jac22 = volt_red * t1.imag();

    
    MatrixXd Jac(jac11.rows() + jac21.rows(), jac11.cols() + jac12.cols());
    Jac <<  jac11, jac12,
            jac21, jac22;

    cout << "\n---out form jac---\n";
    return Jac;
}