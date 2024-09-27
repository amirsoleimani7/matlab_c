#ifndef Header_h
#define Header_h

#include<eigen3/Eigen/Core>
#include<iostream>
#include <cmath>
//#include<complex.h>
#include<vector>

#include"H_NBus.h"
#include"H_Line.h"
// #include "H_tg_con.h"
// #include "H_mac_con.h"

double inverse(double num) ;
double degreeToRadians( double degrees) ;
// MatrixXcf Division_Two_Matrix(MatrixXcf A, MatrixXcf B);
MatrixXd creatMatrixFromLineArray( Line* lineArray ) ;
MatrixXcd Y_Sparse(  NBus *NBusObj  , Line* lineArray) ;

#endif