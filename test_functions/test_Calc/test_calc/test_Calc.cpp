#include "Calc.cpp"

using namespace std;

int main(){
    
    MatrixXd V(13 ,1);

    V <<      1.03,
              1.01,
              0.9781,
              0.95,
              1.0103,
              1.03,
              1.01,
              0.9899,
              0.95,
              0.9876,
              1,
              1.0125,
              0.9938;

    cout << "V IS :\n" << V << "\n";

    MatrixXd ang(13, 1);

    ang << 0.322885911618951,
           0.153588974175501,
           -0.106465084371654,
           -0.174532925199433,
           0.211184839491314,
           -0.118682389135614,
           -0.294960643587042,
           -0.555014702134197,
           -0.610865238198015,
           0.0366519142918809,
           -0.336848545634906,
           -0.23387411976724,
           -0.411897703470662;

    cout << "ang Matrix:\n" << ang << endl;

    Eigen::MatrixXcd Y(13, 13);
    Eigen::MatrixXcd Y_1(13, 6);

    Y_1 << std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0),
         std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 59.8802395209581), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0),
         std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(-9.90099009900990, 99.0099009900990), std::complex<double>(-1.80018001800180, 18.0018001800180), std::complex<double>(0, 0), std::complex<double>(0, 0),
         std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0),
         std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(-3.96039603960396, 39.6039603960396), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0),
         std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 59.8802395209581), std::complex<double>(0, 0),
         std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 59.8802395209581),
         std::complex<double>(11.7011701170117, -311.810451170117), std::complex<double>(0, 200), std::complex<double>(0, 0), std::complex<double>(-1.80018001800180, 18.0018001800180), std::complex<double>(0, 0), std::complex<double>(-9.90099009900990, 99.0099009900990),
         std::complex<double>(0, 200), std::complex<double>(0, -200), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0),
         std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(13.8613861386139, -198.463500907097), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0),
         std::complex<double>(-1.80018001800180, 18.0018001800180), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(3.60036003600360, -33.6186003600360), std::complex<double>(0, 0), std::complex<double>(0, 0),
         std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(3.96039603960396, -99.4623499169977), std::complex<double>(-3.96039603960396, 39.6039603960396),
         std::complex<double>(-9.90099009900990, 99.0099009900990), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(0, 0), std::complex<double>(-3.96039603960396, 39.6039603960396), std::complex<double>(13.8613861386139, -198.463500907097);

    std::cout << "Y_1 Matrix:\n" << Y_1 << std::endl;

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

    cout << "Y is :\n" << Y << "\n";

    MatrixXd Pg(13 ,1);

    Pg << 7.0,
          7.0,
          0.0,
          0.0,
          0.0,
          7.16,
          7.0,
          0.0,
          0.0,
          0.0,
          0.0,
          0.0,
          0.0;

    std::cout << "Pg Matrix:\n" << Pg << std::endl;


    MatrixXd Qg(13, 1);


    Qg << 1.61,
          1.76,
          0.0,
          0.0,
          0.0,
          1.49,
          1.39,
          0.0,
          0.0,
          0.0,
          0.0,
          0.0,
          0.0;

    std::cout << "Qg Matrix:\n" << Qg << std::endl;

    MatrixXd Pl(13, 1);

    Pl << 0.0,
          0.0,
          0.0,
          9.76,
          0.0,
          0.0,
          0.0,
          0.0,
          17.65,
          0.0,
          0.0,
          0.0,
          0.0;

    std::cout << "Pl Matrix:\n" << Pl << std::endl;

    Eigen::MatrixXd Ql(13, 1);

    Ql << 0.0,
          0.0,
          0.0,
          1.0,
          0.0,
          0.0,
          0.0,
          0.0,
          1.0,
          0.0,
          0.0,
          0.0,
          0.0;

    std::cout << "Ql Matrix:\n" << Ql << std::endl;

    
    MatrixXd sw_bno(13, 1);

    sw_bno << 0.0,
              1.0,
              1.0,
              1.0,
              1.0,
              1.0,
              1.0,
              1.0,
              1.0,
              1.0,
              1.0,
              1.0,
              1.0;

    std::cout << "sw_bno Matrix:\n" << sw_bno << std::endl;

    Eigen::MatrixXd g_bno(13, 1);

    g_bno << 1.0,
             0.0,
             1.0,
             1.0,
             1.0,
             0.0,
             0.0,
             1.0,
             1.0,
             1.0,
             1.0,
             1.0,
             1.0;

    std::cout << "g_bno Matrix:\n" << g_bno << std::endl;

    double tol = 1.00E-09;

    cout << "tol is : " << tol << "\n";

      cout << "\n---------------------------\n";
    //void calc(MatrixXd V,MatrixXd ang ,MatrixXcd Y, MatrixXd Pg ,MatrixXd Qg ,MatrixXd Pl ,MatrixXd Ql, MatrixXd sw_bno,MatrixXd g_bno ,double tol)
    calc(V,ang,Y,Pg,Qg,Pl,Ql,sw_bno,g_bno,tol);




    return 0;
}



