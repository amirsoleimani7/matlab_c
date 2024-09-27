#ifndef Header_h
#define Header_h

#include <eigen3/Eigen/Core>
#include <iostream>
#include <cmath>
//#include<complex.h>
#include <vector>
#include "form_jac.cpp"
// #include"H_NBus.h"
// #include"H_Line.h"
// #include "H_tg_con.h"
// #include "H_mac_con.h"

//double inverse(double num) ;
//double degreeToRadians( double degrees) ;
//MatrixXcd Division_Two_Matrix(MatrixXcd A, MatrixXcd B);
// MatrixXf creatMatrixFromLineArray( Line* lineArray ) ;
// MatrixXcf Y_Sparse(  NBus *NBusObj  , Line* lineArray) ;
MatrixXcd Form_Jac_1(MatrixXd V_1, MatrixXd ang_1, MatrixXcd Y_1, MatrixXd ang_red_1, MatrixXd volt_red_1);


#endif