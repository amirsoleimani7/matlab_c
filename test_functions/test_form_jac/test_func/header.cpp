#include "H_header.h"

using namespace Eigen;

double inverse(double num)  {
    return 1.0f / num;
}

double degreeToRadians( double degrees) 
{
    return (degrees * (M_PI / 180.0)) ; //why it was negetive? 
}

// MatrixXf creatMatrixFromLineArray( Line* lineArray )
// {

//     int number_of_cols =  N;
//     MatrixXf resault(NPrime,number_of_cols);
//     for(int i=0 ; i<NPrime ; i++)
//     {
//             resault(i , from_bus_index ) = lineArray[i].from_bus ;
//             resault(i , to_bus_index ) = lineArray[i].to_bus ;
//             resault(i , r_index ) = lineArray[i].r ;
//             resault(i , rx_index ) = lineArray[i].rx ;
//             resault(i , chrg_index ) = lineArray[i].chrg ;
//             resault(i , raw_tap_index ) = lineArray[i].raw_tap ;
//             resault(i , phase_shift_index ) = lineArray[i].phase_shift ;
//             resault(i , tap_max_index ) = lineArray[i].tap_max ;
//             resault(i , tp_min_index ) = lineArray[i].tp_min ;
//             resault(i , tap_size_index ) = lineArray[i].tap_size ;
//     }
//     return resault ;
// }

MatrixXcd  Division_Two_Matrix(MatrixXcd A, MatrixXcd B)
{
    if (B.determinant() != (0.0, 0.0)) {
        MatrixXcd B_inv = B.inverse();
        MatrixXcd result = A * B_inv;
        return result;
    }
    else
    {
        return MatrixXcd::Zero(A.rows(), A.cols());
    }
}
