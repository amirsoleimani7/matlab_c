#include "../include/H_header.h"

using namespace Eigen;


MatrixXcd Y_Sparse(  NBus *NBusObj  , Line* lineArray)
{
    cout << "--------------------in Y_Sparse-----------\n";
    std::complex<double> j(0.0, 1.0);


    VectorXd Gb = NBusObj->getGbArray() ; // (number of busses ,1) -> (13 ,1)
    VectorXd Bb = NBusObj->getBbArray() ; // (number of busses ,1) -> (13 ,1)
    MatrixXcd Y = MatrixXcd::Zero(N, N); //(number of bus,number of bus)... -> (13 ,13)
    
    MatrixXd NLineMatrix = creatMatrixFromLineArray( lineArray ) ; //this is the number of lines , busses (14 ,13)

    //VectorXcf chrg = NLineMatrix.col(chrg_index) ;
    MatrixXcd chrg = NLineMatrix.col(chrg_index).cast<std::complex<double>>();

    MatrixXd r = NLineMatrix.col(r_index) ; // the dimention is (number of lines ,1) -> (14 ,1)

    MatrixXd rx = NLineMatrix.col(rx_index);  // the dim is (14 ,1)

    MatrixXd raw_tap = NLineMatrix.col(raw_tap_index) ; // the dim is (14 ,1)

    MatrixXd phase_shift = NLineMatrix.col(phase_shift_index) ; // the dim is (14 ,1)
        
    
    chrg = (chrg.array() / 2.0 ) * j ;  

    MatrixXcd chrg_sparse  = chrg.asDiagonal();
    MatrixXcd z = r.array() + (rx.array() * j); //z is (14 ,1) -> (number of lines ,1)
 
    // cout << "z is :\n" << z << "\n";
    z = z.array().inverse() ; // z is (14 ,1) -> (numebr of lines ,1)
    // cout << "z is :\n" << z << "\n";


    MatrixXcd y = z.asDiagonal();

    VectorXd temp(NPrime);

    std::complex<double> tap[NPrime];

    for (int i = 0; i < NPrime; i++) {
        temp(i) = 1.0;
        
        if (abs(raw_tap(i)) > 0) {  // Fixing the condition to correctly invert non-zero values
            temp(i) = 1.0 / raw_tap(i);
        }

        complex<double> radian = degreeToRadians(phase_shift(i)) * j;
        radian = exp(radian);

        tap[i] = (temp(i) * radian);
    }

    MatrixXcd c_from = MatrixXcd::Zero(N, NPrime); //(13 ,14) -> (n_bus , n_line)
    MatrixXcd c_to = MatrixXcd::Zero(N, NPrime); //(13 ,14) -> (n_bus,n_line)
    for (int iline = 0; iline < NPrime; iline++) {
        int from = static_cast<int>(lineArray[iline].from_bus);
        int to = static_cast<int>(lineArray[iline].to_bus);
        if (from < N && to < N) {
            c_from(from, iline) = tap[iline];
            c_to(to, iline) = 1;
        }
    }

    MatrixXcd c_line = c_from - c_to;

    Y += c_to * chrg_sparse * c_to.transpose();
    Y += c_from * chrg_sparse * c_from.transpose();
    Y += c_line * y * c_line.transpose();
    // cout << "y is :\n" << Y << "\n";

      
    MatrixXcd tmp = Bb.array() * j ;
    Y += Gb.asDiagonal() + tmp.asDiagonal();
    
        // if( Y.isDiagonal() )
        // {
        //      MatrixXcd tmp = Bb.array() * j ;
        //      Y += Gb.asDiagonal() + tmp.asDiagonal();

        // } 

    cout << "--------------------out Y_Sparse-----------\n";

    return Y ;  

} 