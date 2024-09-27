#include<eigen3/Eigen/Core>
#include <vector>
#include <iostream>
#include <complex>
#include "H_header.h"
// #include "Calc.cpp"
using namespace Eigen;
using namespace std;

int main(){
    
    
    Eigen::MatrixXd bus_sol(13, 15);

    bus_sol << 1, 1.03, 18.5, 7.05364890186703, 1.23953053120829, 0, 0, 0, 0, 1, 5, -1, 22, 1.1, 0.9,
                2, 1.01, 8.76830035392834, 6.99999999999921, 0.843761273386871, 0, 0, 0, 0, 2, 5, -1, 22, 1.1, 0.9,
                3, 1.00551747287907, -5.84234704363831, 0, 0, 3.09e-11, -6.51E-12, 0, 3, 3, 9999, -9999, 230, 1.5, 0.5,
                4, 0.999327628435654, -8.62600457254533, 0, 0, 9.7599999999755, 0.999999999997201, 0, 0, 3, 9999, -9999, 115, 1.05, 0.95,
                5, 1.016357678025, 12.039146157203, 0, 0, 2.20e-12, -5.72e-13, 0, 0, 3, 9999, -9999, 230, 1.5, 0.5,
                6, 1.03, -4.73268228701833, 7.15999999999979, 1.22291484500566, 0, 0, 0, 0, 2, 5, -1, 22, 1.1, 0.9,
                7, 1.01, -14.7063566515766, 6.99999999999859, 0.744532621092242, 0, 0, 0, 0, 2, 5, -1, 22, 1.1, 0.9,
                8, 1.00886090472548, -29.3350872238569, 0, 0, -1.31e-11, -4.72e-12, 0, 5, 3, 9999, -9999, 230, 1.5, 0.5,
                9, 0.999993581119612, -34.3534756058852, 0, 0, 17.6499999999614, 0.99999999999352, 0, 0, 3, 9999, -9999, 115, 1.05, 0.95,
                10, 1.00275089416247, 2.14015834870714, 0, 0, 1.01e-11, -1.85e-12, 0, 0, 3, 9999, -9999, 230, 1.5, 0.5,
                11, 1.05528637043428, -18.0106505165853, 0, 0, 6.99e-12, -1.51e-11, 0, 2, 3, 2, -9999, 500, 1.5, 0.5,
                12, 1.01682078943563, -11.2883736245603, 0, 0, 1.78e-12, -9.71e-14, 0, 0, 3, 9999, -9999, 230, 1.5, 0.5,
                13, 1.00438065719622, -21.3236953536107, 0, 0, 1.84e-11, -2.43e-12, 0, 0, 3, 9999, -9999, 230, 1.5, 0.5;

    std::cout << "bus_sol matrix:\n" << bus_sol << std::endl;

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

    Eigen::MatrixXd load_con(2, 5);

    load_con << 4, 0, 0, 0, 0,
                9, 0, 0, 0, 0;

    std::cout << "load_con matrix:\n" << load_con << std::endl;

    Eigen::MatrixXd mac_con(4, 19);

    mac_con << 1, 1, 900, 0.2, 0, 0, 0.25, 0, 0, 0, 0, 0, 0, 0, 0, 6.5, 0, 0, 1,
               2, 2, 900, 0.2, 0, 0, 0.25, 0, 0, 0, 0, 0, 0, 0, 0, 6.5, 0, 0, 2,
               3, 6, 900, 0.2, 0, 0, 0.25, 0, 0, 0, 0, 0, 0, 0, 0, 6.5, 0, 0, 6,
               4, 7, 900, 0.2, 0, 0, 0.25, 0, 0, 0, 0, 0, 0, 0, 0, 6.5, 0, 0, 7;

    std::cout << "mac_con matrix:\n" << mac_con << std::endl;

    //---------tested above
    complex<double> jay(0, 1);
    double basmva = 100.0;
    int n_line = 14;  // number of lines
    int n_bus = 13;   // number of buses ... defined in the H_NBus.cpp

    int n = mac_con.rows(); // number of generators ... -> [   ==  4 based on the documents
    int nmot = 0 ; // number of induction motors .. -> [    0 ...
    int nig = 0; // number of induction generator .. -> [  0 ...
    
    int ngm = n + nmot;  //
    int n_tot = ngm + nig;  //total number
    
    int nload = load_con.rows();

    MatrixXd J = load_con.col(0);   //this is buss numbers ...

    //----------------
    vector<Bus> buses = createBussesFromMatrix(bus_sol);   //make it so it works in Y_Sparse ...
    NBus nBus(buses);
    vector<Line> lines= createLinesFromMatrix(line);
    //---------------

    MatrixXcd Y_d = Y_Sparse(&nBus , lines.data()); 

    cout << "Y_d is \n" << Y_d << "\n";

    MatrixXd V = bus_sol.col(1); // V from bus_sol

    cout << "V is \n" << V << "\n";

    for(int li = 0; li < nload ; ++li){
        bus_sol((int)J(li) -1, 5) = (1 - load_con(li ,1) - load_con(li,3)) *  bus_sol((int)J(li) -1, 5);    //this needs to be checked ...
        bus_sol((int)J(li) -1, 6) = (1 - load_con(li ,2) - load_con(li,4)) *  bus_sol((int)J(li) -1 , 6);    // aswell as this one ..
    }    
    
    MatrixXd gen_exist = MatrixXd::Zero(n_bus , 1);    // the number of busses(n_bus ,1)
    
    for (int li = 0; li < n_bus; ++li) {
        for(int index = 0; index < mac_con.rows() ; ++index){
            if (li == (int)mac_con(index, 1) -1){
                gen_exist(li ,0) = (int)mac_con(index, 0);   //this needs to be checked for sure ...
            }
        }
    }
    
    cout << "gen_exist is \n" << gen_exist << "\n";
    
    MatrixXd Pl = bus_sol.col(5);     // Pl (n_bus ,1)
    MatrixXd Ql = bus_sol.col(6);     // Ql (n_bus ,1)



    MatrixXd netgen = MatrixXd::Zero(n_bus ,1);

    // indexing needs checking ...
    for (int li = 0; li < n_bus; ++li) {
        if(gen_exist(li ,0) == 0) {
            netgen(li ,0) = li;
            Pl(li) = Pl(li) - bus_sol(li ,3); // Pl = Pl - Pg ..
            Ql(li) = Ql(li) - bus_sol(li ,4);  // Ql = Ql - Qg ...
        }
    }
    
    cout << "netgen is \n" << netgen << "\n";
    
    //     Pg = bus.col(3); //matrix for Pg
    //     Qg = bus.col(4); //... ... Qg
    //     Pl = bus.col(5); //... ... Pl
    //     Ql = bus.col(6); // ... ... Ql

    MatrixXcd yl = MatrixXd::Zero(n_bus , n_bus);
    
    for (int li = 0; li < n_bus; ++li) {
        yl(li , li) = ((Pl(li ,0) - (Ql(li, 0) * jay )) / (V(li ,0) * V(li ,0)));
    }

    cout << "yl is \n" << yl << "\n";
    Y_d += yl;
    cout << "Y_d is \n" << Y_d << "\n";


    MatrixXd ra(n , 1);   // indexing ... (4 ,1)
    for(int i = 0; i < n;++i){
        ra(i ,0) = (mac_con(i ,4) * basmva) / mac_con(i ,2);
    }
    cout << "ra is \n" << ra << "\n";

    MatrixXd testxp = MatrixXd::Zero(n,1);

    MatrixXd testxpp = MatrixXd::Ones(n,1);

    vector<int> txpp;
    vector<int> txp;

    // n = mac_con.rows();

    for (int k = 0; k < n; ++k ) {
        if (mac_con(k, 7) == 0) {
            testxp(k ,0) = 1;
            testxpp(k ,0) = 0;
        }
    }

    for(int k = 0; k < n;++k){
        if(testxpp(k ,0) == 1){
            txpp.push_back(k);
        }
        if(testxp(k ,0) == 1){
            txp.push_back(k);
        }
    }
    
    
    MatrixXd Xd = MatrixXd::Zero(n , 1);

    if (txpp.size() != 0){
        for(int li = 0; li < n;++li){
            if (find(txpp.begin(), txpp.end(), li) != txpp.end()) {
                Xd(li) = (mac_con(li ,7) * basmva) / mac_con(li ,2);
            }
        }
    }

    
    if (txp.size() != 0){
        for(int li = 0; li < n;++li){
            if (find(txp.begin(), txp.end(), li) != txp.end()) {
                Xd(li) = (mac_con(li ,6) * basmva) / mac_con(li ,2);
            }
        }
    }

    cout << "Xd is \n" << Xd << "\n"; 
    MatrixXcd y(n ,1);

    for (int i = 0; i < n; ++i) {
        y(i ,0) = 1.0 / (ra(i ,0) + jay * Xd(i,0));
    }

    cout << "y is \n" << y << "\n";


    MatrixXd Jg(0 ,1);

    for (int li = 0; li < n_bus; ++li) {
        if ((gen_exist(li , 0) != 0)) { // FIND FUNCTION NEEDS TO BE checked
            cout << "li is : " << li << "\n"; 
            Jg.conservativeResize(Jg.rows() + 1, NoChange);
            Jg(Jg.rows()- 1, 0) = li +1; //bus numbers
        }
    }

    cout << "Jg is\n" << Jg << "\n";

    MatrixXd perm = MatrixXd::Zero(Jg.rows(), n);  // Initialize perm with zeros

    for (int li = 0; li < mac_con.rows(); ++li) {
        int bus_num = mac_con(li, 1);
        for (int index = 0; index < Jg.rows(); ++index) {
            if (Jg(index, 0) == bus_num) {
                perm(index, li) = 1.0;  // Set the corresponding element to 1
            }
        }
    }

    MatrixXcd Ymod = y.asDiagonal() * perm.transpose();
    
    MatrixXd bus_order = MatrixXd::Zero(n_bus, 1);

    int J_size = J.rows();  // Get the actual size of J
    for (int li = 0; li < J_size; ++li) {
        bus_order(li, 0) = J(li, 0);
    }

    int index = J_size;
    for (int li = 1; li < n_bus +1; ++li) {
        bool found = false;
        for (int lj = 0; lj < J_size; ++lj) {
            if (J(lj, 0) == li) {
                found = true;
                break;
            }
        }

        if (!found) {
            bus_order(index, 0) = li;
            index++;
        }
    }
  
    cout << "bus order is \n" << bus_order << "\n";

    MatrixXd p = MatrixXd::Zero(n_bus, n_bus);

    for (int li = 0; li < n_bus; ++li) {
        int order = static_cast<int>(bus_order(li, 0)) - 1;  // Subtract 1 to convert to zero-based index
        if (order >= 0 && order < n_bus) {  // Ensure the index is within bounds
            p(li, order) = 1;
        }
    }

    
    MatrixXcd Y_b = MatrixXcd::Zero(n_tot ,n_bus);

    cout << "Ymod is \n" << Ymod << "\n";
    cout << "Jg is \n" << Jg << "\n";

    cout << "n_tot is  : " << n_tot << "\n"; 
    cout << "Jg.rows() is  : " << Jg.rows() << "\n"; 

    for (int li = 0; li < n_tot; ++li) {  // Loop over rows
        for (int lj = 0; lj < Jg.rows(); ++lj) {  // Loop over indices in Jg
            int col_idx = Jg(lj, 0) - 1;  // Convert from 1-based to 0-based index
            cout << "col_index is : " << col_idx << "\n"; 
            // Debugging output
            if (col_idx < 0 || col_idx >= n_bus) {
                cerr << "Error: Index " << col_idx << " is out of bounds for Y_b." << endl;
            } else {
                Y_b(li, col_idx) = -Ymod(li, lj);  // Assign negative Ymod value to Y_b
            }
        }
    }

    // Output the result
    cout << "Y_b is \n" << Y_b << "\n";


    MatrixXcd Y_a = MatrixXcd::Zero(n_tot ,n_tot);
    for(int li = 0; li < n_tot  ; ++li){
        Y_a(li,li) = y(li ,0);
    }

    cout << "Y_a is \n" << Y_a << "\n";

        // // Assuming Y_b is an (n_bus x n_bus) matrix
    // MatrixXd Y_b1 = Y_b.block(0, 0, Y_b.rows(), nload);            // First nload columns
    // MatrixXd Y_b2 = Y_b.block(0, nload, Y_b.rows(), n_bus - nload); // Columns from nload+1 to n_bus


    return 0;
}
