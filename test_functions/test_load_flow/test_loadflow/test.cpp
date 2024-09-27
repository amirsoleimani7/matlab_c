#include<eigen3/Eigen/Core>
#include <vector>
#include <iostream>
#include <complex>
#include "H_header.h"
// #include "Calc.cpp"



using namespace Eigen;
using namespace std;

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



MatrixXd safeInverse(const MatrixXd& mat) {
    MatrixXd invMat = mat.array().inverse();

    // Iterate over the elements to check for NaN
    for(int i = 0; i < invMat.rows(); ++i) {
        for(int j = 0; j < invMat.cols(); ++j) {
            if(std::isnan(invMat(i, j)) || std::isinf(invMat(i ,j))) {
                invMat(i, j) = 0.0; // Replace NaN with 0
            }
        }
    }

    return invMat;
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

MatrixXcd safeInverse(const MatrixXcd& mat) {
    MatrixXcd invMat = mat.array().inverse();

    // Iterate over the elements to check for NaN
    for(int i = 0; i < invMat.rows(); ++i) {
        for(int j = 0; j < invMat.cols(); ++j) {
            if(std::isnan(invMat(i, j).real()) || std::isnan(invMat(i, j).imag())) {
                invMat(i, j) = complex<double> (0.0, 0.0); // Replace NaN with 0
            }
        }
    }

    return invMat;
}
int main(){
    
    Eigen::MatrixXd bus(13, 15);

    bus << 1, 1.03, 18.5, 7, 1.61, 0, 0, 0, 0, 1, 5, -1, 22, 1.1, 0.9,
            2, 1.01, 8.8, 7, 1.76, 0, 0, 0, 0, 2, 5, -1, 22, 1.1, 0.9,
            3, 0.9781, -6.1, 0, 0, 0, 0, 0, 3, 3, 9999, -9999, 230, 1.5, 0.5,
            4, 0.95, -10, 0, 0, 9.76, 1, 0, 0, 3, 9999, -9999, 115, 1.05, 0.95,
            5, 1.0103, 12.1, 0, 0, 0, 0, 0, 0, 3, 9999, -9999, 230, 1.5, 0.5,
            6, 1.03, -6.8, 7.16, 1.49, 0, 0, 0, 0, 2, 5, -1, 22, 1.1, 0.9,
            7, 1.01, -16.9, 7, 1.39, 0, 0, 0, 0, 2, 5, -1, 22, 1.1, 0.9,
            8, 0.9899, -31.8, 0, 0, 0, 0, 0, 5, 3, 9999, -9999, 230, 1.5, 0.5,
            9, 0.95, -35, 0, 0, 17.65, 1, 0, 0, 3, 9999, -9999, 115, 1.05, 0.95,
            10, 0.9876, 2.1, 0, 0, 0, 0, 0, 0 , 3, 9999, -9999, 230, 1.5, 0.5,
            11, 1, -19.3, 0, 0, 0, 0, 0, 2, 3, 2, -9999, 500, 1.5, 0.5,
            12, 1.0125, -13.4, 0, 0, 0, 0, 0, 0, 3, 9999, -9999, 230, 1.5, 0.5,
            13, 0.9938, -23.6, 0, 0, 0, 0, 0, 0, 3, 9999, -9999, 230, 1.5, 0.5;

    std::cout << "bus Matrix:\n" << bus << std::endl;

    Eigen::MatrixXd line(14, 10);

    line << 1, 5, 0, 0.0167, 0, 1, 0, 0, 0, 0,
            2, 10, 0, 0.0167, 0, 1, 0, 0, 0, 0,
            3, 4, 0, 0.005, 0, 1, 0, 1.2, 0.8, 0.02,
            3, 10, 0.001, 0.01, 0.0175, 1, 0, 0, 0, 0,
            3, 11, 0.011, 0.11, 0.1925, 1, 0, 0, 0, 0,
            3, 11, 0.011, 0.11, 0.1925, 1, 0, 0, 0, 0,
            5, 10, 0.0025, 0.025, 0.0437, 1, 0, 0, 0, 0,
            6, 12, 0, 0.0167, 0, 1, 0, 0, 0, 0,
            7, 13, 0, 0.0167, 0, 1, 0, 0, 0, 0,
            8, 11, 0.011, 0.11, 0.1925, 1, 0, 0, 0, 0,
            8, 11, 0.011, 0.11, 0.1925, 1, 0, 0, 0, 0,
            8, 9, 0, 0.005, 0, 1, 0, 1.2, 0.8, 0.02,
            8, 13, 0.001, 0.01, 0.0175, 1, 0, 0, 0, 0,
            12, 13, 0.0025, 0.025, 0.0437, 1, 0, 0, 0, 0;

    std::cout << "line matrix:\n" << line << std::endl;


    vector<Bus> busses = createBussesFromMatrix(bus);

    double swing_index;
    double swing_index_1;

    // for(int i = 0; i < busses.size() ;++i){
    //     if(busses[i].busType == 1){
    //         swing_index = busses[i].Bus_no;
    //     }
    // }
    for(int i = 0; i < busses.size() ;++i){
        if(busses[i].busType == 1){
            swing_index_1 = busses[i].Bus_no;
        }
    }

    for(int i = 0; i < bus.rows() ;++i){
        if(bus(i,9) == 1){
            swing_index = bus(i ,0);
        }
    }

    cout << "swing index is : " << swing_index << "\n"; 
    
    vector<double> PQV_no;
    for(int i = 0; i < busses.size() ;++i){
        if(busses[i].busType >= 2){
            PQV_no.push_back(busses[i].Bus_no);
        }
    }
    
    for(int i =0;i <PQV_no.size();++i ){
        cout << PQV_no[i] << "\n";
    }
    
    MatrixXd PQV_no_m(PQV_no.size() ,1);
        
    for(int i =0;i <PQV_no.size();++i ){
        PQV_no_m(i) = PQV_no[i];
    }
     
    cout << PQV_no_m << "\n";

    // cout << "index is "<< swing_index << "\n";


    vector<int> sw_bno_m;

    for(int i = 1; i < 14 ;++i )
    {
        cout << "i ; " << i << " swing_index ; "<< swing_index << "\n";
        if(i == swing_index){
            cout<< "we are here\n";
            int num = 0;
            sw_bno_m.push_back(num);
        }
        else{
            cout << "we are here1\n";
            int num = 1;
            sw_bno_m.push_back(num);
        }
    }


    for(int i = 0;i <13;++i){
        cout << sw_bno_m[i] << " ";
    }

    MatrixXd sw_bno(13, 1);
    for(int i = 0;i < sw_bno_m.size();++i){
        sw_bno(i,0) = sw_bno_m[i]; 
    }

    cout << "sw_bno is ;\n" << sw_bno << "\n";

    vector<double> gen_index_m;
    for(int i = 0; i < busses.size() ;++i){
        if(busses[i].busType ==  2){
            gen_index_m.push_back(busses[i].Bus_no);
        }
    }   

    MatrixXd gen_index(gen_index_m.size() ,1);    //gen_index matrix ...    //bus_type == 2

    for(int i =0;i <gen_index_m.size();++i ){
        gen_index(i) = gen_index_m[i];
    }

    vector<int> g_bno_m;

    for(int i = 1; i < 14 ;++i )
    {
        // cout << "i ; " << i << " swing_index ; "<< swing_index << "\n";
        int flag = 1;
        for(int j = 0;j<gen_index_m.size();++j){
            if (i == gen_index_m[j]){
                g_bno_m.push_back(0);
                flag = 0;
                break;
            }
        }
        if(flag){
            g_bno_m.push_back(1);
        }
    }

    MatrixXd g_bno(g_bno_m.size(),1);
    for(int i = 0;i<g_bno_m.size();++i){
        g_bno(i,0) = g_bno_m[i];
    }


    int il_for_ang_red = PQV_no_m.size();
    // cout << "il is : " << il_for_ang_red << "\n";
    // MatrixXd ang_red(il_for_ang_red,13);
    // cout << "rows : " <<ang_red.rows() << " cols :" << ang_red.cols() << "\n";
    // vector<int> ii;
    
    // for(int i = 1;i < il_for_ang_red +1;++i){
    //     ii.push_back(i);
    // }
    
    // for(int i = 1;i <il_for_ang_red +1; ++i){   //i goes (1 ,10)
    //     int j = PQV_no_m(i);
    //     ang_red(i,j) = 1;
    // }
    
    // cout << "ang_red is \n" << ang_red << "\n"; 
    

    // int il_for_ang_red = PQV_no_m.size();
    // cout << "il is : " << il_for_ang_red << "\n";
    int nbus = bus.rows();


    vector<double> PQ_no_m;
    for(int i = 0; i < busses.size() ;++i){
        if(busses[i].busType == 3){
            PQ_no_m.push_back(busses[i].Bus_no);
        }
    }   

    MatrixXd PQ_no(PQ_no_m.size() ,1);    //PQ_no matrix ...    //bus_type == 3

    for(int i =0;i <PQ_no.size();++i ){
        PQ_no(i) = PQ_no_m[i];
    }

    // int il_volt_red = PQ_no_m.size();
    // MatrixXd volt_red(il_volt_red,nbus +1); // not sure about the +1 it should be checked for sure ...
    // volt_red.setZero();
    // vector<int> ii_volt_red;

    // for(int i = 0; i < il_volt_red ;++i){
    //     ii_volt_red.push_back(i);
    // }

    // for(int i = 0; i < il_volt_red;++i){
    //     int j = static_cast<int>(PQ_no(i,0));
    //     volt_red(i,j) = 1; 
    // }


    // cout << "volt_red is \n" << volt_red << "\n"; 

    // Output the results
    // cout << "First part: \n" << first_part << endl;
    // cout << "Second part: \n" << second_part << endl;

    // cout << "modified temp is \n" << temp * 2 << "\n";

    VectorXd V = bus.col(1);
    // Minimum and maximum voltage limits

    // Ensure all elements in V are at least volt_min

    // Output the result

    MatrixXd volt_min = bus.col(14);
    cout << "old v is \n" << V << "\n";

    for(int i = 0 ;i<V.size();++i){
        if(V(i) <volt_min(i)){
            V(i) = volt_min(i);
        }
    }

    cout << "new v is \n" << V << "\n";

 
    MatrixXd bus_type = bus.col(9);// ...

    cout << " bus_type is\n"<<  bus_type << "\n";


    cout << "line is \n" << line << "\n";
    cout << "from_bus is \n" << line.col(0) << "\n";
    cout << "to_bus is \n" << line.col(1) << "\n";

    MatrixXd tap_ratio(line.rows() ,1);
    for(int i = 0; i < line.rows();++i){
        if(line(i ,5) == 0){
            tap_ratio(i,0) = 1;
        }
        tap_ratio(i,0) = line(i ,5);
    }

    MatrixXd ang = bus.col(2).array() * (M_PI / 180.0);  //ang matrix and turn them to radian ....
    
    complex<double> jay(0.0 , 1.0);
    MatrixXcd ang_complex = (ang.array() *jay).exp();
    MatrixXcd V_rect = V.array() * ang_complex.array();
    MatrixXcd VV = V_rect;

    cout << "VV is \n" << VV << "\n";

    MatrixXd phase_shift = line.col(6);
    cout << "pahse shift is \n" << phase_shift << "\n";
    MatrixXcd phase_shift_complex = phase_shift * (M_PI / 180.0) * jay;
    phase_shift_complex = phase_shift_complex.array().exp();


    cout << "tap_ratio is \n" << tap_ratio << "\n";
    cout << "phase_shift_complex  is \n" << phase_shift_complex << "\n";

    MatrixXcd tps = tap_ratio.array() * phase_shift_complex.array();


    cout << "tps is \n" << tps << "\n";
    MatrixXd from_bus  = line.col(0);
    MatrixXd to_bus = line.col(1);
    MatrixXd r = line.col(2);
    MatrixXd rx= line.col(3);
    MatrixXd chrg = line.col(4);
    MatrixXcd z = r.array() + (rx.array() * jay);
    MatrixXcd y = z.array().inverse();

    cout << "z IS \n" << z << "\n";
    cout << "y IS \n" << y << "\n";
   
    /*
    MW_s = VV(from_int).*conj((VV(from_int) - tps.*VV(to_int)).*y ...
   + VV(from_int).*(jay*chrg/2))./(tps.*conj(tps));    
    */
    MatrixXd i = from_bus;
    MatrixXd j = to_bus;

    int nline = line.rows();

    MatrixXcd MW_s(line.rows() ,1);
    for(int k = 0; k < line.rows();k++){

        // complex<double> x_1 = VV((int)i(k) -1);    //cast to int to make sure ....
        
        // complex<double> x_21 = VV((int)i(k) -1);                                   // First part: VV(i(k))
        // complex<double> x_22 = tps(k) * VV((int)j(k) -1) * y(k);                   // Second part: tps(k) * VV(j(k)) * y(k)
        // complex<double> x_23 = VV((int)i(k) -1) * jay * chrg(k) / 2.0;             // Third part: VV(i(k)) * jay * chrg(k) / 2.0
        // complex<double> x_2 = x_21 - x_22 + x_23;
        // complex<double> x_3 = (tps(k) * conj(tps(k)));
        
        // MW_s(k,0) = x_1 * conj(x_2 / x_3);
            complex<double> x_1 = VV((int)i(k) - 1);    // VV(from_int)
            complex<double> x_21 = VV((int)i(k) - 1);  // VV(from_int)
            complex<double> x_22 = tps(k) * VV((int)j(k) - 1);  // tps(k) * VV(to_int)
            
            complex<double> x_2 = conj((x_21 - x_22) * y(k) + x_21 * jay * chrg(k) / 2.0);  // Apply conjugate after full expression
            complex<double> x_3 = tps(k) * conj(tps(k));  // tps * conj(tps)

            MW_s(k, 0) = x_1 * x_2 / x_3;
    }
    cout << "MW_s is \n" << MW_s << "\n";

    MatrixXd P_s = MW_s.real();
    MatrixXd Q_s = MW_s.imag();

    cout << "\n---------------------\n";
    cout << "VV is \n" << VV << "\n size is : " << VV.size() << "\n";
    cout << "tps is \n" << tps << "\nsize is : " << tps.size() << " \n";
    cout << "y is \n" << y << "\nsize is : " << y.size() << "\n";
    cout << "ang is \n" << ang << "\nsize is : " << ang.size() << "\n";
    cout << "j is :\n" << j << "\nsize is  " << j.size() << "\n"; 
    cout << "i is :\n" << i << " \nsize is : " << i.size() << "\n"; 
    cout << "chrg is :\n" << chrg << "\n size is "<< chrg.size() << "\n"; 

    for(int k = 0; k < line.rows(); k++) {
        cout << "i(" << k << ") = " << (int)i(k) << ", j(" << k << ") = " << (int)j(k) << endl;
    }


    MatrixXcd MW_r(line.rows() ,1);
    for(int k = 0; k < line.rows() ;k++)
    {
        complex<double> x_1 = VV((int)j(k) -1);    //cast to int to make sure ....
        complex<double> x_2 = (((VV((int)j(k) - 1) -(VV((int)i(k) - 1))) / tps(k)) * y(k)) + (VV((int)j(k) -1) * jay * chrg(k) / 2.0);
        x_2 = conj(x_2);
        MW_r(k,0) = x_1 * x_2;
    }   

    MatrixXd P_r = MW_r.real();
    MatrixXd Q_r = MW_r.imag();

    MatrixXd iline(line.rows() ,1);
    for (int i = 1;i <line.rows()+1;++i){
        iline(i-1 ,0) = i;
    }

    MatrixXd line_ffrom(line.rows() ,5);
    line_ffrom << iline , from_bus , to_bus , P_s ,Q_s;
    // cout << "line_ffrom is \n" << line_ffrom << "\n"; 

    MatrixXd line_fto(nline ,5);
    line_fto << iline , to_bus , from_bus , P_r ,Q_r;

    MatrixXd line_flow(2*nline ,5);
    line_flow <<line_ffrom,
                line_fto;
    
    cout << "line_flow is \n"<< line_flow << "\n";


    MatrixXd line_sol = line;
    cout << "line_sol \n" << line_sol << "\n";
    cout << "0=----------------------\n";
    // vector<Bus> busses = createBussesFromMatrix(bus);   //make it so it works in Y_Sparse ...
    NBus nBus(busses);
    vector<Line> lines= createLinesFromMatrix(line);
    
    MatrixXcd Y = Y_Sparse(&nBus,lines.data());


    //----------------------------------------
    MatrixXd ang_red(il_for_ang_red, nbus);
    ang_red.setZero();

    cout << "rows : " << ang_red.rows() << " cols : " << ang_red.cols() << "\n";

    vector<int> ii;

    // Fill the ii vector with values from 0 to il_for_ang_red - 1
    for(int i = 0; i < il_for_ang_red; ++i) {
        ii.push_back(i);
    }

    // Populate ang_red matrix
    
    for(int i = 0; i < il_for_ang_red; ++i) {   // Loop from 0 to il_for_ang_red - 1
        int j = static_cast<int>(PQV_no_m(i)) -1;  // Ensure j is treated as an integer
        cout << "i ;" << i << " j " << j << "\n";   

        ang_red(i, j) = 1;
    }

    cout << "ang_red is \n" << ang_red << "\n";
    //-------------------------------------------
     int il_volt_red = PQ_no_m.size();
    MatrixXd volt_red(il_volt_red,nbus ); // not sure about the +1 it should be checked for sure ...
    volt_red.setZero();
    vector<int> ii_volt_red;

    for(int i = 0; i < il_volt_red ;++i){
        ii_volt_red.push_back(i);
    }

    for(int i = 0; i < il_volt_red;++i){
        int j = static_cast<int>(PQ_no(i,0)) -1;
        volt_red(i,j) = 1; 
    }

    // MatrixXcd Jac = Form_Jac_1(V,ang,Y,ang_red,volt_red);


    MatrixXd Pg = bus.col(3); //matrix for Pg
    MatrixXd Qg = bus.col(4); //matrix for Qg
    MatrixXd Pl = bus.col(5); //matrix for Pl
    MatrixXd Ql = bus.col(6); //matrix for Ql

    double tol = 1.00E-09;
    MatrixXd delP, delQ, P, Q;
    int conv_flag;
    calc(V, ang, Y, Pg, Qg, Pl, Ql, sw_bno, g_bno, tol, delP, delQ, P, Q, conv_flag);

    cout << "delP is : \n" << delP << "\n";
    cout << "delQ is : \n" << delQ << "\n";
    cout << "P is : \n" << P << "\n";
    cout << "Q is : \n" << Q << "\n";
    cout << "conv_flag is : \n" << conv_flag << "\n";


    cout << "swing index is : " << swing_index << "\n"; 
    cout << "swing index_1 is : " << swing_index_1 << "\n"; 

    // MatrixXd red_delP = ang_red * delP;
    // MatrixXd red_delQ = volt_red * delQ;
    // MatrixXd vertical_concatination(red_delP.rows() + red_delQ.rows(),1);
    // cout << "Jac is \n" <<  Jac << "\n" << Jac.rows() << " " << Jac.cols() << "\n";
    // Jac  = safeInverse(Jac);
    // cout << "Jac is \n" <<  Jac << "\n" << Jac.rows() << " " << Jac.cols() << "\n";

    // MatrixXcd temp = Jac * vertical_concatination;
    // cout << "temp is \n" << temp << "\n";

    
    MatrixXd PQV_no_1(0, 1);

    // Iterate over rows and add elements dynamically
    for(int i = 0; i < bus.rows(); ++i) {
        if(bus(i, 9) >= 2) {
            PQV_no_1.conservativeResize(PQV_no_1.rows() + 1, NoChange);
            PQV_no_1(PQV_no_1.rows() - 1, 0) = bus(i, 0);
        }
    }


    MatrixXd PQ_no_11(0 ,1);    //PQ_no matrix ...    //bus_type == 3

    for(int i =0;i <PQ_no.size();++i ){
        if(bus(i ,9) == 3){
            PQ_no_11.conservativeResize(PQ_no_11.rows() +1, NoChange);
            PQ_no_11(PQ_no_11.rows() - 1, 0) = bus(i, 0);
        }
    }

    MatrixXd g_bno_1 = MatrixXd::Ones(nbus, 1);  // Initialize g_bno with 1s

    for(int i = 1; i < 14; ++i) {
        for(int j = 0; j < gen_index.rows(); ++j) {
            if(i == gen_index(j, 0)) {
                g_bno_1(i - 1, 0) = 0;  // Set corresponding g_bno element to 0
            break;  // No need to continue inner loop
            }
        }
    }

    cout << "V  is\n" << V << "\n"; 
    cout << "ang is\n" << ang << "\n"; 
    cout << "Y  is\n" << Y << "\n"; 
    cout << "Pg  is\n" << Pg << "\n"; 
    cout << "Qg  is\n" << Qg << "\n"; 
    cout << "Pl  is\n" << Pl << "\n"; 
    cout << "Ql  is\n" << Ql << "\n"; 
    cout << "sw_bno  is\n" << sw_bno << "\n"; 
    cout << "g_bno  is\n" << g_bno << "\n"; 

    cout << "first g_bno is \n" << g_bno_1 << "\n";
    cout << "second g_bno is \n" << g_bno << "\n";



    // cout << "PQ_no is \n" << PQ_no_11 << "\n";

    // cout << "PQV_no is \n" << PQV_no_1 << "\n";
    
    // cout << "------------------------\n";


    MatrixXd Jac = Form_Jac_1(V, ang, Y, ang_red, volt_red);
    cout << "Jac is \n" << Jac << "\n";

    // Debugging the vertical concatenation construction
    MatrixXd red_delP = ang_red * delP;
    cout << "red_delP is \n" << red_delP << "\n";

    MatrixXd red_delQ = volt_red * delQ;
    cout << "red_delQ is \n" << red_delQ << "\n";

    MatrixXd vertical_concatination(red_delP.rows() + red_delQ.rows(), 1);
    
    vertical_concatination << red_delP, red_delQ;

    cout << "VEERTICAL CONCATINATION IS \n" << vertical_concatination << "\n";

    // Ensure Jac is invertible
    if (Jac.determinant() != 0) {
        MatrixXd Jac_inv = Jac.inverse();
        cout << "Jac.inverse is \n" << Jac_inv << "\n";

        MatrixXd temp = Jac_inv * vertical_concatination;
        cout << "temp is \n" << temp << "\n";

        MatrixXd temp_1 = temp.block(0, 0, PQV_no.size(), temp.cols());
        MatrixXd temp_2 = temp.block(PQV_no.size(), 0, temp.rows() - PQV_no.size(), temp.cols());

        cout << "temp_1 is \n" << temp_1 << "\n";
        cout << "temp_2 is \n" << temp_2 << "\n";

        MatrixXd delAng = ang_red.transpose() * temp_1;
        MatrixXd delV = volt_red.transpose() * temp_2;

        cout << "delAng is \n" << delAng << "\n";
        cout << "delV is \n" << delV << "\n";
    } else {
        cout << "Jac is singular, cannot invert.\n";
    }

//     cout << "MW_r is\n" << MW_r << "\n";

// //     complex<double> x_1 = VV((int)j(k) -1);    //cast to int to make sure ....
// // complex<double> x_2 = (((VV((int)j(k) - 1) -(VV((int)i(k) - 1))) / tps(k)) * y(k)) + (VV((int)j(k) -1) * jay * chrg(k) / 2.0);
// // x_2 = conj(x_2);
// // MW_r(k,0) = x_1 * x_2;

//     cout << "VV is \n" << VV <<"\n"; 
//     cout << "tps is \n" << tps <<"\n"; 
//     cout << "y is \n" << y <<"\n"; 
//     cout << "chrg is \n" << chrg <<"\n"; 


}
