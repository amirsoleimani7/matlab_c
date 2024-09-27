#include "H_header.h"

using namespace Eigen;

double inverse(double num)  {
    return 1.0 / num;
}

double degreeToRadians( double degrees) 
{
    return (degrees *(-1) * (M_PI / 180.0)) ; //why it was negetive? 
}

MatrixXd creatMatrixFromLineArray( Line* lineArray )
{

    int number_of_cols =  N;
    MatrixXd resault(NPrime,number_of_cols);
    for(int i=0 ; i<NPrime ; i++)
    {
            resault(i , from_bus_index ) = lineArray[i].from_bus ;
            resault(i , to_bus_index ) = lineArray[i].to_bus ;
            resault(i , r_index ) = lineArray[i].r ;
            resault(i , rx_index ) = lineArray[i].rx ;
            resault(i , chrg_index ) = lineArray[i].chrg ;
            resault(i , raw_tap_index ) = lineArray[i].raw_tap ;
            resault(i , phase_shift_index ) = lineArray[i].phase_shift ;
            resault(i , tap_max_index ) = lineArray[i].tap_max ;
            resault(i , tp_min_index ) = lineArray[i].tp_min ;
            resault(i , tap_size_index ) = lineArray[i].tap_size ;
    }
    return resault ;
}

// MatrixXcf  Division_Two_Matrix(MatrixXcf A, MatrixXcf B)
// {
//     if (B.determinant() != (0.0f, 0.0f)) {
//         MatrixXcf B_inv = B.inverse();
//         MatrixXcf result = A * B_inv;
//         return result;
//     }
//     else
//     {
//         return MatrixXcf::Zero(A.rows(), A.cols());
//     }
// }
