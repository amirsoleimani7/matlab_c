#include "H_header.h"

using namespace Eigen;

double inverse(double num)  {
    return 1.0 / num;
}

double degreeToRadians( double degrees) 
{
    return (degrees  *(-1.0)* (M_PI / 180.0)) ; //why it was negetive? 
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

MatrixXcd Division_Two_Matrix(MatrixXcd A, MatrixXcd B)
{
    MatrixXcd result(A.rows(), A.cols());

    for(int j = 0; j < A.cols(); ++j) {
        std::complex<double> divisor = B(j, j);

        if (divisor != std::complex<double>(0, 0)) {
            for(int i = 0; i < A.rows(); ++i) {
                result(i, j) = A(i, j) / divisor;
            }
        } else {
            for(int i = 0; i < A.rows(); ++i) {
                result(i, j) = std::complex<double>(0, 0); 
            }
        }
    }
    
    return result;
}
vector<Bus> createBussesFromMatrix(MatrixXd& matrix) {
    vector<Bus> busses;
    for (int i = 0; i < matrix.rows(); ++i) {
        // Extract row data
        double Bus_no = matrix(i, 0);
        double V = matrix(i, 1);
        double tmp_ang = matrix(i, 2);
        double Pg = matrix(i, 3);
        double Qg = matrix(i, 4);
        double Pl = matrix(i, 5);
        double Ql = matrix(i, 6);
        double Gb = matrix(i, 7);
        double Bb = matrix(i, 8);
        int bus_type = static_cast<int>(matrix(i,9));
        double qg_max = matrix(i, 10);
        double qg_min = matrix(i, 11);
        double v_rate = matrix(i, 12);
        double v_max = matrix(i, 13);
        double v_min = matrix(i, 14);

        // Create a Bus object
        Bus bus;

        bus.tmp_ang = tmp_ang; 
        bus.Bus_no = Bus_no;
        bus.V = V;
        bus.Pg = Pg;
        bus.Qg = Qg;
        bus.Pl = Pl;
        bus.Ql = Ql;
        bus.Gb = Gb;
        bus.Bb = Bb;
        bus.qg_max = qg_max;
        bus.qg_min = qg_min;
        bus.v_rate = v_rate;
        bus.v_max = v_max;
        bus.v_min = v_min;
        switch (bus_type) {
            case 1:
                bus.busType = Swing;
                break;
            case 2:
                bus.busType = PV;
                break;
            case 3:
                bus.busType = PQ;
                break;
        }

        // Add to vector
        busses.push_back(bus);
    }
    return busses;
}

vector<Line> createLinesFromMatrix(const MatrixXd& matrix) {
    vector<Line> lines;
    for (int i = 0; i < matrix.rows(); ++i) {
        // Extract row data
        double fromBus = matrix(i, 0) -1;
        double toBus = matrix(i, 1) -1;
        double resistance = matrix(i, 2);
        double reactance = matrix(i, 3);
        double chrg = matrix(i, 4);
        double raw_tap = matrix(i, 5);
        double phase_shift= matrix(i, 6);
        double tap_max = matrix(i, 7);
        double tap_min = matrix(i, 8);
        double tap_size = matrix(i, 9);
        
        // Create a Line object
        Line line;
        line.from_bus = fromBus;
        line.to_bus = toBus;
        line.r =  resistance;
        line.rx = reactance;
        line.chrg = chrg;
        line.raw_tap = raw_tap;
        line.phase_shift = phase_shift;
        line.tap_max = tap_max;
        line.tp_min = tap_min;
        line.tap_size = tap_size;

        // Add to vector
        lines.push_back(line);
    }
    return lines;
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
