#include<eigen3/Eigen/Core>
#include<iostream>
#include <complex>

using namespace std;
using namespace Eigen;

// calc(V,ang,Y,Pg,Qg,Pl,Ql,sw_bno,g_bno,tol)

void calc(MatrixXd V,MatrixXd ang ,MatrixXcd Y, MatrixXd Pg ,MatrixXd Qg ,MatrixXd Pl ,MatrixXd Ql, MatrixXd sw_bno,MatrixXd g_bno ,double tol)
{

    complex<double> jay(0.0 , 1.0);
    MatrixXd delP, delQ ,P , Q;
    int conv_flag = 0;


    MatrixXcd ang_complex = (ang.array() * jay).exp();
    MatrixXcd V_rect = V.array() * ang_complex.array();

    // cout << Y << "\n";




    // Initialize Cur_inj to be the same size as Y
    
    MatrixXcd Cur_inj(Y.rows(), Y.cols());

    // cout << Cur_inj.rows() << " " << Cur_inj.cols() << "\n";

    Cur_inj = Y * V_rect;

    // for(int i = 0;i<13;++i){
    //     for(int j = 0 ;j < 6;++j){
    //         Cur_inj(i,j) = Y(i,j) * V_rect(i,0);
    //     }
    // }
    // cout << "we are here" << "\n";
    // cout << "Cur_inj is \n" << Cur_inj << "\n";


    MatrixXcd S = Cur_inj.conjugate().array() * V_rect.array();

    // cout << Cur_inj.rows() << " " << Cur_inj.cols() << "\n";
    // cout << V_rect.rows() << " " << V_rect.cols() << "\n";
    // MatrixXcd S(Cur_inj.rows(),Cur_inj.cols());

    // std::cout << "Cur_inj dimensions: " << Cur_inj.rows() << " x " << Cur_inj.cols() << std::endl;
    // std::cout << "V_rect dimensions: " << V_rect.rows() << " x " << V_rect.cols() << std::endl;
    // std::cout << "S dimensions: " << S.rows() << " x " << S.cols() << std::endl;

    // int counter = 0;
    // for(int i = 0;i<13;++i){
    //     for(int j = 0 ;j < 6;++j){
    //         cout << Cur_inj(i,j) * complex<double> (0.0 ,-1.0)* V_rect(i,0) << " ";
    //         cout << "(i,j) " << i<< " " << j << "\n";
    //         counter ++;
    //     }
    // }

    P = S.real();
    Q = S.imag();


    delQ = (Qg - Ql - Q);
    delP = (Pg - Pl - P);

    /*
    delP=delP.*sw_bno;
    delQ=delQ.*sw_bno;
    delQ=delQ.*g_bno;
    */


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

    cout << "delP is : \n" << delP << "\n";
    cout << "delQ is : \n" << delQ << "\n";
    cout << "P is : \n" << P << "\n";
    cout << "Q is : \n" << Q << "\n";
    cout << "conv_flag is : \n" << conv_flag << "\n";

};
    
