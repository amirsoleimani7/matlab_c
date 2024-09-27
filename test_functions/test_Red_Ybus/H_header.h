#ifndef Header_h
#define Header_h

#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Dense>
#include <iomanip>
#include <chrono>

#include<iostream>
#include <cmath>
#include<complex>
#include<vector>

#include"H_NBus.h"
#include"H_Line.h"

double inverse(double num) ;
double degreeToRadians( double degrees) ;

MatrixXd creatMatrixFromLineArray( Line* lineArray ) ;
MatrixXd Form_Jac_1(MatrixXd V, MatrixXd ang, MatrixXcd Y, MatrixXd ang_red, MatrixXd volt_red);
MatrixXcd Y_Sparse(  NBus *NBusObj  , Line* lineArray);
MatrixXcd Division_Two_Matrix(MatrixXcd A, MatrixXcd B);
void calc(MatrixXd V,MatrixXd ang ,MatrixXcd Y, MatrixXd Pg ,MatrixXd Qg ,MatrixXd Pl ,MatrixXd Ql, MatrixXd sw_bno,MatrixXd g_bno ,double tol,
        MatrixXd& delP,MatrixXd& delQ,MatrixXd& P ,MatrixXd& Q,int& conv_flag);
int chq_lim(MatrixXd& bus,MatrixXd& Qg, MatrixXd& Ql,MatrixXd& qg_max ,MatrixXd& qg_min);
MatrixXd safeInverse(const MatrixXd& mat);
vector<Line> createLinesFromMatrix(const MatrixXd& matrix);
vector<Bus> createBussesFromMatrix(MatrixXd& matrix);
void load_flow(MatrixXd bus, MatrixXd line, double tol, double iter_max, double acc ,string display ,double flag);
void lftap(MatrixXd& bus,MatrixXd& V,MatrixXd& volt_min ,MatrixXd& volt_max, MatrixXd& line);
void red_ybus(MatrixXd& bus_sol, MatrixXd& line , MatrixXd& mac_con, MatrixXd& load_con,double basmva);

#endif