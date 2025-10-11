#include "H_header.h"

using namespace std;
using namespace Eigen;

// calc(V,ang,Y,Pg,Qg,Pl,Ql,sw_bno,g_bno,tol)

void calc(MatrixXd V,MatrixXd ang ,MatrixXcd Y, MatrixXd Pg ,MatrixXd Qg ,MatrixXd Pl ,MatrixXd Ql, MatrixXd sw_bno,MatrixXd g_bno ,double tol,
        MatrixXd& delP,MatrixXd& delQ,MatrixXd& P ,MatrixXd& Q,int& conv_flag)
{
    cout << "\n---in Calc---\n";
    complex<double> jay(0.0 , 1.0);
 
    MatrixXcd ang_complex = (ang.array() * jay).exp();
    MatrixXcd V_rect = V.array() * ang_complex.array();

    MatrixXcd Cur_inj(Y.rows(), Y.cols());

    Cur_inj = Y * V_rect;

    MatrixXcd S = Cur_inj.conjugate().array() * V_rect.array();

    P = S.real();
    Q = S.imag();

    delQ = (Qg - Ql - Q);
    delP = (Pg - Pl - P);

    delP = delP.cwiseProduct(sw_bno);

    delQ = delQ.cwiseProduct(sw_bno);
    delQ = delQ.cwiseProduct(g_bno);

    double Pmis = delP.cwiseAbs().maxCoeff(); 
    double Qmis = delQ.cwiseAbs().maxCoeff();

    double mism =  Pmis + Qmis;

    if(mism>tol)
    {
        conv_flag=1;
    }
    else conv_flag=0;

    cout<< "\n---out calc----\n";

};
    
