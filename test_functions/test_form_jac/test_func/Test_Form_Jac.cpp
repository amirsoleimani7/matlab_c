
// #include <eigen3/Eigen/Core>

#include "form_jac.cpp"
#include "math.h"
#include <iomanip>
#include <fstream>
#include <string>

#include <algorithm>
#include <cctype>

using namespace std;
using namespace Eigen;


Eigen::MatrixXd readCSV(const std::string &file, int rows, int cols) {
    std::ifstream in(file);
    std::string line;
    Eigen::MatrixXd mat(rows, cols);
    int row = 0;
    
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string value;
        int col = 0;
        
        while (std::getline(ss, value, ',')) {
            mat(row, col++) = std::stod(value);
        }
        row++;
    }
    return mat;
}



Eigen::MatrixXcd readComplexCSV(const std::string &file, int rows, int cols) {
    std::ifstream in(file);
    std::string line;
    Eigen::MatrixXcd mat(rows, cols);
    int row = 0;

    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string value;
        int col = 0;

        while (std::getline(ss, value, ',')) {
            // Remove any whitespace
            value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());

            std::complex<double> complex_number(0.0, 0.0);

            if (value == "0") {
                // Handle "0"
                complex_number = std::complex<double>(0.0, 0.0);
            } else if (value.find('i') != std::string::npos) {
                // Handle pure imaginary number like "3i"
                if (value == "i") {
                    complex_number = std::complex<double>(0.0, 1.0);
                } else if (value == "-i") {
                    complex_number = std::complex<double>(0.0, -1.0);
                } else {
                    complex_number = std::complex<double>(0.0, std::stod(value.substr(0, value.length() - 1)));
                }
            } else if (value.find('+') != std::string::npos || value.find('-') != std::string::npos) {
                // Handle numbers with both real and imaginary parts like "2+3i" or "2-3i"
                size_t imag_pos = value.find('i');
                size_t plus_pos = value.find('+', 1);
                size_t minus_pos = value.find('-', 1);

                if (plus_pos != std::string::npos) {
                    double real = std::stod(value.substr(0, plus_pos));
                    double imag = std::stod(value.substr(plus_pos + 1, imag_pos - plus_pos - 1));
                    complex_number = std::complex<double>(real, imag);
                } else if (minus_pos != std::string::npos) {
                    double real = std::stod(value.substr(0, minus_pos));
                    double imag = std::stod(value.substr(minus_pos, imag_pos - minus_pos));
                    complex_number = std::complex<double>(real, imag);
                }
            } else {
                // Handle pure real numbers like "2"
                complex_number = std::complex<double>(std::stod(value), 0.0);
            }

            mat(row, col++) = complex_number;
        }
        row++;
    }
    return mat;
}



















int main(){

    // Eigen::MatrixXd V = readCSV("V.csv", 13, 1);

    // std::cout << "Matrix V:\n" << V << std::endl;

    // Eigen::MatrixXd ang = readCSV("ang.csv", 13, 1);

    // std::cout << "Matrix ang:\n" << ang << std::endl;

    // Eigen::MatrixXcd Y = readComplexCSV("Y.csv", 13, 13);

    // std::cout << "Matrix Y:\n" << Y << std::endl;

    // Eigen::MatrixXd ang_red = readCSV("ang_red.csv", 12, 13);
    // std::cout << "ang_Red is  :\n" << ang_red << std::endl;
 
    // Eigen::MatrixXd volt_red = readCSV("volt_red.csv", 9, 13);
    // std::cout << "volt_red is  :\n" << volt_red << std::endl;

   cout << setprecision(7) ;

    // creating V matrix ...
    Eigen::MatrixXd V(13, 1);  // 13x1 V of double

    V(0, 0) = 1.03;
    V(1, 0) = 1.01;
    V(2, 0) = 0.9781;
    V(3, 0) = 0.95;
    V(4, 0) = 1.0103;
    V(5, 0) = 1.03;
    V(6, 0) = 1.01;
    V(7, 0) = 0.9899;
    V(8, 0) = 0.95;
    V(9, 0) = 0.9876;
    V(10, 0) = 1.0;
    V(11, 0) = 1.0125;
    V(12, 0) = 0.9938;

    cout << "V is :\n" << V << "\n";


    Eigen::MatrixXd ang(13, 1);  // 13x1 matrix of double

    ang(0, 0) = 0.322885911618951;
    ang(1, 0) = 0.153588974175501;
    ang(2, 0) = -0.106465084371654;
    ang(3, 0) = -0.174532925199433;
    ang(4, 0) = 0.211184839491314;
    ang(5, 0) = -0.118682389135614;
    ang(6, 0) = -0.294960643587042;
    ang(7, 0) = -0.555014702134197;
    ang(8, 0) = -0.610865238198015;
    ang(9, 0) = 0.0366519142918809;
    ang(10, 0) = -0.336848545634906;
    ang(11, 0) = -0.23387411976724;
    ang(12, 0) = -0.411897703470662;

    Eigen::IOFormat fullPrecision(Eigen::FullPrecision);
    std::cout << ang.format(fullPrecision) << std::endl;
    cout << "ang is: \n" <<  sin(ang(0)) << "\n";    


    // //creating a matrix of Y


    Eigen::MatrixXcd Y(13, 13);  // 13x13 complex matrix

    Y(0, 0) = std::complex<double>(0, -59.8802395209581);
    Y(0, 4) = std::complex<double>(0, 59.8802395209581);

    Y(1, 1) = std::complex<double>(0, -59.8802395209581);
    Y(1, 9) = std::complex<double>(0, 59.8802395209581);

    Y(2, 2) = std::complex<double>(11.7011701170117, -313.810451170117);
    Y(2, 3) = std::complex<double>(0, 200.000000000000);
    Y(2, 9) = std::complex<double>(-9.90099009900990, 99.0099009900990);
    Y(2, 10) = std::complex<double>(-1.80018001800180, 18.0018001800180);

    Y(3, 2) = std::complex<double>(0, 200.000000000000);
    Y(3, 3) = std::complex<double>(0, -200.000000000000);

    Y(4, 0) = std::complex<double>(0, 59.8802395209581);
    Y(4, 4) = std::complex<double>(3.96039603960396, -99.4623499169977);
    Y(4, 9) = std::complex<double>(-3.96039603960396, 39.6039603960396);

    Y(5, 5) = std::complex<double>(0, -59.8802395209581);
    Y(5, 11) = std::complex<double>(0, 59.8802395209581);

    Y(6, 6) = std::complex<double>(0, -59.8802395209581);
    Y(6, 12) = std::complex<double>(0, 59.8802395209581);

    Y(7, 7) = std::complex<double>(11.7011701170117, -311.810451170117);
    Y(7, 8) = std::complex<double>(0, 200.000000000000);
    Y(7, 10) = std::complex<double>(-1.80018001800180, 18.0018001800180);
    Y(7, 12) = std::complex<double>(-9.90099009900990, 99.0099009900990);

    Y(8, 7) = std::complex<double>(0, 200.000000000000);
    Y(8, 8) = std::complex<double>(0, -200.000000000000);

    Y(9, 1) = std::complex<double>(0, 59.8802395209581);
    Y(9, 2) = std::complex<double>(-9.90099009900990, 99.0099009900990);
    Y(9, 4) = std::complex<double>(-3.96039603960396, 39.6039603960396);
    Y(9, 9) = std::complex<double>(13.8613861386139, -198.463500907097);

    Y(10, 2) = std::complex<double>(-1.80018001800180, 18.0018001800180);
    Y(10, 7) = std::complex<double>(-1.80018001800180, 18.0018001800180);
    Y(10, 10) = std::complex<double>(3.60036003600360, -33.6186003600360);

    Y(11, 5) = std::complex<double>(0, 59.8802395209581);
    Y(11, 11) = std::complex<double>(3.96039603960396, -99.4623499169977);
    Y(11, 12) = std::complex<double>(-3.96039603960396, 39.6039603960396);

    Y(12, 6) = std::complex<double>(0, 59.8802395209581);
    Y(12, 7) = std::complex<double>(-9.90099009900990, 99.0099009900990);
    Y(12, 11) = std::complex<double>(-3.96039603960396, 39.6039603960396);
    Y(12, 12) = std::complex<double>(13.8613861386139, -198.463500907097);

    cout << "Y is \n" << Y <<"\n";

    Eigen::MatrixXd ang_red(12, 13);  // 12x13 matrix of double

    // ang_red << 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //            0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //            0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //            0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    //            0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    //            0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    //            0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    //            0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    //            0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    //            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    //            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    //            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1;


    ang_red << 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
               0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
               0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
               0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
               0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
               0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
               0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
               0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
               0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
               0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
               0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
               0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0;

    cout << " ang_red is :\n" << ang_red << "\n";

    Eigen::MatrixXd volt_red(9, 13);  // 19x13 matrix of double

    // volt_red << 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //             0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //             0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    //             0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    //             0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    //             0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,  
    //             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    //             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    //             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1;


     volt_red <<    0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                    0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                    0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                    0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,
                    0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,
                    0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,
                    0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,
                    0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,
                    0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0;

    cout << " volt-red  is :\n" << volt_red << "\n";


    
    cout << "--------------------------------\n";

    complex<double> jay_1(1000.1234, 1000.0004);
    complex<double> jay_2(1000.1234, 1000.0003);
  

    cout << " + is " << jay_1 + jay_2 << "\n"; 
    cout << " - is " << jay_1 - jay_2 << "\n"; 

    cout << "--------------------------------\n";



    MatrixXcd jac = Form_Jac_1(V,ang,Y,ang_red,volt_red);

    // for(int i = 0;i<21 ;++i){
    //     for(int j = 0;j<21 ;++j){
    //         cout << jac(i,j) .real()<< "";
    //     }
    //     cout << "\n";
    // }

    cout << "Jac is \n" << jac.real() << "\n";

    return 0;

}

/*


*/