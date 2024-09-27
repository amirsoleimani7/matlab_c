#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
//#include <complex>
#include "H_header.h"

using namespace std;
//using namespace Eigen;

vector<string> split(const string &str, char delimiter) {
    vector<string> tokens;
    string token;
    stringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<Bus> readBuses(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    string line;
    getline(file, line);  // Skip header

    vector<Bus> busses;

    while (getline(file, line)) {
        vector<string> row = split(line, ',');
        if (row.size() < 15) {
            cerr << "Invalid row: " << line << endl;
            continue;
        }

        Bus bus;
        bus.Bus_no = stof(row[0]);
        bus.V = stof(row[1]);
        bus.tmp_ang = stof(row[2]);
        bus.Pg = stof(row[3]);
        bus.Qg = stof(row[4]);
        bus.Pl = stof(row[5]);
        bus.Ql = stof(row[6]);
        bus.Gb = stof(row[7]);
        bus.Bb = stof(row[8]);
        float busType = stof(row[9]);
        bus.qg_max = stof(row[10]);
        bus.qg_min = stof(row[11]);
        bus.v_rate = stof(row[12]);
        bus.v_max = stof(row[13]);
        bus.v_min = stof(row[14]);

        if(busType == 1) {                                         
            bus.busType = Swing;                               
        } else if(busType == 2) {
            bus.busType = PV;
        } else {
            bus.busType = PQ;
        }

        busses.push_back(bus);
    }

    file.close();
    return busses;
}

vector<Line> readLines(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    string line;
    getline(file, line);  // Skip header

    vector<Line> lines;

    while (getline(file, line)) {
        vector<string> row = split(line, ',');
        if (row.size() < 10) {
            cerr << "Invalid row: " << line << endl;
            continue;
        }

        Line line;
        line.from_bus = stof(row[0]) -1;
        line.to_bus = stof(row[1]) -1;
        line.r = stof(row[2]);
        line.rx = stof(row[3]);
        line.chrg = stof(row[4]);
        line.raw_tap = stof(row[5]);
        line.phase_shift = stof(row[6]);
        line.tap_max = stof(row[7]);
        line.tp_min = stof(row[8]);
        line.tap_size = stof(row[9]);

        lines.push_back(line);
    }

    file.close();
    return lines;
}



int main() {

    // cout << "we are here\n";
    
    // cout<<"error_(-1)\n";
    vector<Bus> busses = readBuses("input_bus.csv");
    vector<Line> lines = readLines("input_line.csv");
    
    // cout << "busses size is " << busses.size() <<"\n"; //there are 13 bus objects
    // cout << "lines size is " << lines.size() <<"\n";    //there are 14 line objects
    // cout << "the N is : "<< N<< "\n";
    // cout << "the NPrime is : "<< NPrime <<"\n";

    // for (const auto& line : lines) {
    // cout << "From Bus: " << line.from_bus << ", To Bus: " << line.to_bus << ", R: " << line.r 
    //      << ", RX: " << line.rx << ", Chrg: " << line.chrg << ", Raw Tap: " << line.raw_tap
    //      << ", Phase Shift: " << line.phase_shift << ", Tap Max: " << line.tap_max 
    //      << ", Tp Min: " << line.tp_min << ", Tap Size: " << line.tap_size << endl;
    // }

    // MatrixXf NLineMatrix = creatMatrixFromLineArray(lines.data());
    // cout << "Matrix:\n" << NLineMatrix << endl;

    // cout <<"\ntest for complex numbers in eigen\n";
    // std::complex<double> complex_number(2.0, 3.0);

    // // Create a 3x3 matrix of ones
    // Eigen::Matrix<std::complex<double>, 3, 3> matrix_of_ones;
    // matrix_of_ones.setOnes();

    // // Multiply the matrix by the complex number
    // Eigen::Matrix<std::complex<double>, 3, 3> result = matrix_of_ones * complex_number;

    // // Print the result
    // std::cout << "Resulting matrix:\n" << result << std::endl;
    // cout <<"-----------------------------\n";

    // cout<<"error_0\n";
    NBus nBus(busses);
    MatrixXcd Y = Y_Sparse(&nBus, lines.data());
    cout << "Y-Sparse Matrix:\n";

    for(int i = 0; i < Y.rows(); ++i) {
        for(int j = 0; j < Y.cols(); ++j) {
            std::complex<double> value = Y(i, j);
            double realPart = value.real();
            double imagPart = value.imag();
            
            // Formatting output: Real part + Imaginary part with 'i' without parentheses
            cout << realPart;
            if (imagPart >= 0) {
                cout << " + " << imagPart << "i";
            } else {
                cout << " - " << -imagPart << "i";
            }
            if (j < Y.cols() - 1) {
                cout << " , "; // Add a comma only if it's not the last element in the row
            }
        }
        cout << "\n"; // New line after each row
    }

    return 0;
}
