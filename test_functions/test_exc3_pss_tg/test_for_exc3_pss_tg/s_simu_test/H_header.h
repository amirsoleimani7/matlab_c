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

void load_flow(MatrixXd bus, MatrixXd line, double tol, double iter_max, double acc ,string display ,double flag,MatrixXd& bus_sol_1 ,MatrixXd& line_sol_1,MatrixXd& line_flow_1);

void lftap(MatrixXd& bus,MatrixXd& V,MatrixXd& volt_min ,MatrixXd& volt_max, MatrixXd& line);

void red_ybus(MatrixXd bus_sol, MatrixXd line , MatrixXd mac_con, MatrixXd load_con,double basmva, MatrixXcd&  Y_gprf,
        MatrixXcd& Y_gncprf,MatrixXcd& Y_ncgprf, MatrixXcd& Y_ncprf, MatrixXcd& V_rgprf, MatrixXcd& V_rncprf, MatrixXd& boprf);

void y_switch(MatrixXd& bus, MatrixXd& line,MatrixXd& load_con, MatrixXd& mac_con, MatrixXd& sw_con);

void mac_em(MatrixXd bus ,MatrixXd mac_con ,MatrixXd bus_int ,MatrixXd mac_em_idx,
        double i ,double k , double flag ,double n_em,double basmva);

void mac_sub(MatrixXd bus, MatrixXd mac_con, MatrixXd bus_int, MatrixXd mac_sub_idx,
    double i ,double k, double flag ,double n_sub, double basmva);
    
void exc_indx(MatrixXd& exc_con, MatrixXd& exc_pot, int& n_exc, 
              MatrixXd& st3_idx, int& n_st3,
              MatrixXd& st3_TA, MatrixXd& st3_TA_idx, MatrixXd& st3_noTA_idx,
              MatrixXd& st3_TB, MatrixXd& st3_TB_idx, MatrixXd& st3_noTB_idx,
              MatrixXd& st3_TR, MatrixXd& st3_TR_idx, MatrixXd& st3_noTR_idx);

void mac_indx(MatrixXd& mac_con , MatrixXd&  mac_pot , int& n_mac);

void pss_indx(MatrixXd& pss_con, MatrixXd& mac_con, MatrixXd& exc_con, 
              MatrixXd& pss_idx, int& n_pss, MatrixXd& pss_sp_idx, 
              MatrixXd& pss_p_idx, MatrixXd& pss_mb_idx, MatrixXd& pss_exc_idx, 
              MatrixXd& pss_T, MatrixXd& pss_T2, MatrixXd& pss_T4, 
              MatrixXd& pss_T4_idx, MatrixXd& pss_noT4);

void Tg_idx(MatrixXd& tg_con, MatrixXd& tg_idx, int& n_tg, MatrixXd& tgh_idx, int& n_tgh);



void pss(int i, int flag, MatrixXd& pss_con,MatrixXd& Tclead1, MatrixXd& Tclead2 , MatrixXd Tclag1 ,MatrixXd& pss_idx,MatrixXd& pss_pot,MatrixXd& mac_int,MatrixXd& pss_p_idx , MatrixXd& pss_mb_idx, MatrixXd& pss_exc_idx,
         MatrixXd& pss1, MatrixXd& pss_T4_idx , MatrixXd& pss_T4,MatrixXd& pss2, MatrixXd& pss3, MatrixXd& pss_out, MatrixXd& dpw_pss_idx, 
         MatrixXd& dpw_out, MatrixXd& mac_con, MatrixXd& mac_spd, MatrixXd& pelect, MatrixXd& pss_sp_idx ,double basmva);

void exc_st3(
    MatrixXd &exc_con, const MatrixXd &mac_con,const MatrixXd &mac_pot, const MatrixXd &bus_int, 
    const MatrixXd &mac_int, const MatrixXd &vex, const MatrixXd &pelect, 
    const MatrixXd &qelect, const MatrixXd &eterm, const MatrixXd &theta, 
    const MatrixXd &fldcur, MatrixXd &Efd, MatrixXd &exc_pot, 
    MatrixXd &V_B, MatrixXd &V_R, MatrixXd &V_A, MatrixXd &V_As, 
    MatrixXd &V_TR, MatrixXd &R_f, const MatrixXd &st3_idx, 
    const MatrixXd &st3_TB_idx);

void tg(MatrixXd &mac_int , MatrixXd &tg_con ,MatrixXd &tg_idx , MatrixXd &pmech , int n_tg);

void s_simu(MatrixXd& bus,MatrixXd& line,MatrixXd& mac_con,MatrixXd& load_con,MatrixXd& exc_con,
             MatrixXd& pss_con , MatrixXd& tg_con ,MatrixXd& sw_con);


#endif