#ifndef Header_h
#define Header_h

// #include<eigen3/Eigen/Core>
// #include<eigen3/Eigen/Dense>

#include "../third_party/Eigen/Core"
#include "../third_party/Eigen/Dense"

#include <iomanip>
#include <chrono>

#include<iostream>
#include <cmath>
#include<complex>
#include<vector>

#include <fstream>

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

void load_flow(MatrixXd bus, MatrixXd line, double tol, double iter_max, double acc ,string display ,double flag  , MatrixXd &bus_sol_1 , MatrixXd &line_sol_1 , MatrixXd &line_flow_1);

void lftap(MatrixXd& bus,MatrixXd& V,MatrixXd& volt_min ,MatrixXd& volt_max, MatrixXd& line);

void red_ybus(MatrixXd bus_sol, MatrixXd line , MatrixXd mac_con, MatrixXd load_con,double basmva, MatrixXcd&  Y_gprf,
        MatrixXcd& Y_gncprf,MatrixXcd& Y_ncgprf, MatrixXcd& Y_ncprf, MatrixXcd& V_rgprf, MatrixXcd& V_rncprf, MatrixXd& boprf);

void y_switch(MatrixXd& bus, MatrixXd& line,MatrixXd& load_con, MatrixXd& mac_con, MatrixXd& sw_con);


void mac_em(
        MatrixXd bus, MatrixXd mac_con, MatrixXd bus_int, MatrixXd mac_em_idx,
        int  i, int k, double flag, int  &n_em, double &basmva,
        MatrixXd &mac_pot,
        MatrixXd &eterm, MatrixXd &pelect, MatrixXd &qelect, MatrixXd &phi,
        MatrixXd &psi_re, MatrixXd &psi_im, MatrixXd &mac_ang, MatrixXd &mac_spd,
        MatrixXd &eqprime, MatrixXd &vex, MatrixXd &edprime, MatrixXd &busnum,
        MatrixXd &curqg, MatrixXd &curdg, MatrixXd &eq, MatrixXd &ed,
        MatrixXd &curq, MatrixXd &curd, MatrixXd &pmech, MatrixXd &theta,
        MatrixXcd &V, MatrixXcd &curr, MatrixXcd &eprime, MatrixXcd &ei, MatrixXcd &rot
    );
    
void mac_tra(
        MatrixXd &bus, MatrixXd &mac_con, MatrixXd &bus_int, MatrixXd &mac_tra_idx,
        int &i, int &k, double &flag, int  &n_tra, double &basmva,
        MatrixXd &mac_pot,
        MatrixXd &cur_re, MatrixXd &cur_im, 
        MatrixXd &psidpp, MatrixXd &psikd, MatrixXd &psikq, MatrixXd &psiqpp,
        MatrixXd &psi_re, MatrixXd &psi_im,
        MatrixXd &mac_ang, MatrixXd &mac_spd, MatrixXd &eqprime, MatrixXd &edprime,
        MatrixXd &curd, MatrixXd &curq, MatrixXd &curdg, MatrixXd &curqg, MatrixXd &fld_cur,
        MatrixXd &vex, MatrixXd &eterm, MatrixXd &theta, MatrixXd &ed, MatrixXd &eq,
        MatrixXd &pmech, MatrixXd &pelect, MatrixXd &qelect,
        MatrixXd &dmac_ang, MatrixXd &dmac_spd, MatrixXd &deqprime, MatrixXd &dedprime,
        MatrixXd &mcurmag,
        MatrixXd &busnum, MatrixXd &phi, MatrixXd &eqra, MatrixXd &E_Isat, MatrixXd &edra,
        MatrixXcd &curr, MatrixXcd &V, MatrixXcd &ei, MatrixXcd &rot, MatrixXcd &eprime
        );

void mac_sub(
        int i,            // (Unused; originally "i")
        int flag,
        const MatrixXd &bus,
        MatrixXd &mac_con,
        const MatrixXd &bus_int,
        const MatrixXd &mac_sub_idx,
        double n_sub,         // number of subtransient machines
        double basmva,
        MatrixXd &mac_pot,
        MatrixXd &cur_re,
        MatrixXd &cur_im,
        MatrixXd &psidpp,
        MatrixXd &psikd,
        MatrixXd &psikq,
        MatrixXd &psiqpp,
        MatrixXd &psi_re,
        MatrixXd &psi_im,
        MatrixXd &mac_ang,
        MatrixXd &mac_spd,
        MatrixXd &eqprime,
        MatrixXd &edprime,
        MatrixXd &curd,
        MatrixXd &curq,
        MatrixXd &curdg,
        MatrixXd &curqg,
        MatrixXd &fld_cur,
        MatrixXd &vex,
        MatrixXd &eterm,
        MatrixXd &theta,
        MatrixXd &ed,
        MatrixXd &eq,
        MatrixXd &pmech,
        MatrixXd &pelect,
        MatrixXd &qelect,
        MatrixXd &dmac_ang,
        MatrixXd &dmac_spd,
        MatrixXd &deqprime,
        MatrixXd &dedprime,
        MatrixXd &mcurmag,
        MatrixXd &busnum,
        MatrixXd &phi,
        MatrixXd &eqra,
        MatrixXd &E_Isat,
        MatrixXd &edra,
        MatrixXcd &curr,
        MatrixXcd &V,
        MatrixXcd &ei,
        MatrixXcd &rot
        );
        
void exc_indx(MatrixXd& exc_con, MatrixXd& exc_pot, int& n_exc, 
              MatrixXd& st3_idx, int& n_st3,
              MatrixXd& st3_TA, MatrixXd& st3_TA_idx, MatrixXd& st3_noTA_idx,
              MatrixXd& st3_TB, MatrixXd& st3_TB_idx, MatrixXd& st3_noTB_idx,
              MatrixXd& st3_TR, MatrixXd& st3_TR_idx, MatrixXd& st3_noTR_idx);

void mac_indx(MatrixXd& mac_con, MatrixXd& mac_pot, MatrixXd& mac_em_idx, 
              MatrixXd& mac_tra_idx, MatrixXd& mac_sub_idx, MatrixXd& mac_int, 
              int& macmax, int& n_mac, int& n_tot, int& n_ig, int& n_em, 
              int& n_tra, int& n_sub , MatrixXd &not_ib_idx , int &ngm);
              
void pss_indx(MatrixXd& pss_con, MatrixXd& mac_con, MatrixXd& exc_con, 
              MatrixXd& pss_idx, int& n_pss, MatrixXd& pss_sp_idx, 
              MatrixXd& pss_p_idx, MatrixXd& pss_mb_idx, MatrixXd& pss_exc_idx, 
              MatrixXd& pss_T, MatrixXd& pss_T2, MatrixXd& pss_T4, 
              MatrixXd& pss_T4_idx, MatrixXd& pss_noT4);

void Tg_idx(MatrixXd& tg_con, MatrixXd& tg_idx, int& n_tg, MatrixXd& tgh_idx, int& n_tgh);



void pss(int i, int flag, MatrixXd& pss_con,MatrixXd& Tclead1, MatrixXd& Tclead2 , MatrixXd Tclag1 ,MatrixXd& pss_idx,MatrixXd& pss_pot,MatrixXd& mac_int,MatrixXd& pss_p_idx , MatrixXd& pss_mb_idx, MatrixXd& pss_exc_idx,
         MatrixXd& pss1, MatrixXd& pss_T4_idx , MatrixXd& pss_T4,MatrixXd& pss2, MatrixXd& pss3, MatrixXd& pss_out, MatrixXd& dpw_pss_idx, 
         MatrixXd& dpw_out, MatrixXd& mac_con, MatrixXd& mac_spd, MatrixXd& pelect, MatrixXd& pss_sp_idx ,double basmva);


void exc_st3( int i, int flag, int n_sub , int n_tra ,
    MatrixXd &exc_con, 
    const MatrixXd &mac_con,
    const MatrixXd &mac_pot, 
    const MatrixXd &bus_int, 
    const MatrixXd &mac_int, 
    const MatrixXd &vex, 
    const MatrixXd &pelect, 
    const MatrixXd &qelect, 
    const MatrixXd &eterm, 
    const MatrixXd &theta, 
    const MatrixXd &fldcur, 
    MatrixXd &Efd, 
    MatrixXd &exc_pot, 
    MatrixXd &V_B, 
    MatrixXd &V_R, 
    MatrixXd &V_A, 
    MatrixXd &V_As, 
    MatrixXd &V_TR, 
    MatrixXd &R_f, 
    const MatrixXd &st3_idx, 
    const MatrixXd &st3_TB_idx, 
    MatrixXcd &iterm,   // Output: complex matrix
    MatrixXcd &vep,     // Output: complex matrix
    MatrixXcd &ve,      // Output: complex matrix
    MatrixXd &F_EX,     
    MatrixXd &n,        // Output: machine number vector
    MatrixXd &n_bus,    // Output: bus index vector
    MatrixXd &low_IN,   // Output: list of low current indices
    MatrixXd &V_I, 
    MatrixXd &V_E , 
    MatrixXd &I_N);      // Output: V_I values


void tg(int i, int flag, 
MatrixXd &mac_int, 
MatrixXd &tg_con, 
MatrixXd &tg_idx, 
MatrixXd &pmech, 
int n_tg,
MatrixXd &tg1,
MatrixXd &tg2,
MatrixXd &tg3,
MatrixXd &tg_pot,
MatrixXd &tg_sig,
MatrixXd &n_tg_mat);
void s_simu(MatrixXd& bus,MatrixXd& line,MatrixXd& mac_con,MatrixXd& load_con,MatrixXd& exc_con,
             MatrixXd& pss_con , MatrixXd& tg_con ,MatrixXd& sw_con);


void nc_load(MatrixXd &bus , int falg , MatrixXd &load_con,
            MatrixXd &j  ,MatrixXcd &V_nc  , MatrixXcd &S_cc , MatrixXcd &load_pot
);
      

// functions for saving the data of flag0
// void writeRealVector(ofstream &f, const string &name, const MatrixXd &v);
// void writeComplexVector(ofstream &f, const string &name, const MatrixXcd &v);

// void save_exc_st3_outputs(
//     const string &filename,
//     const MatrixXcd &iterm,
//     const MatrixXcd &vep,
//     const MatrixXcd &ve,
//     const MatrixXd &F_EX,
//     const MatrixXd &Efd,
//     const MatrixXd &V_B,
//     const MatrixXd &V_R,
//     const MatrixXd &V_A,
//     const MatrixXd &V_As,
//     const MatrixXd &V_TR,
//     const MatrixXd &R_f,
//     const MatrixXd &V_I,
//     const MatrixXd &V_E,
//     const MatrixXd &I_N,
//     const MatrixXd &low_IN,
//     const MatrixXd &n_bus_mat,
//     const MatrixXd &n_mat,
//     const MatrixXd &st3_idx     
// );

// void save_tg_outputs(
//     const string &filename,
//     const MatrixXd &tg1,
//     const MatrixXd &tg2,
//     const MatrixXd &tg3,
//     const MatrixXd &tg_pot,
//     const MatrixXd &tg_sig,
//     const MatrixXd &n_tg_mat
// );

void save_maccon_matrix(ofstream &f, const MatrixXd &mac_con, const string &filename);
void save_macpot_matrix(ofstream &f, const MatrixXd &matrix, const string &filename);

#endif