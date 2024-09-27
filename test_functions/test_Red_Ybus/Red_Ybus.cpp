#include "H_header.h"

using namespace std;
using namespace Eigen;
/*

    bus_no = bus.col(0);   //matrix for bus numbers ...(nbus ,1);for all the below lines ...
    V = bus.col(1);    //matrix for v
    ang = bus.col(2).array() * (M_PI / 180.0);  //ang matrix and turn them to radian ....
    Pg = bus.col(3); //matrix for Pg
    Qg = bus.col(4); //... ... Qg
    Pl = bus.col(5); //... ... Pl
    Ql = bus.col(6); // ... ... Ql
    Gb = bus.col(7); //    ...
    Bb = bus.col(8); //    ...
    bus_type = bus.col(9);// this is bustype  
    qg_max = bus.col(10);
    qg_min = bus.col(11);
    volt_max  = bus.col(13);
    volt_min  = bus.col(14);
    
    /-------------------
    
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
*/

void print_func(MatrixXcd mat,int rows ,int cols){

    for(int i = 0; i < rows ;++i){
        for(int j = 0; j < cols ;++j){
            std::cout << mat(i ,j).real() << ", " << mat(i ,j).imag() << "i, ";
        }
        cout << "\n";
    }
    cout << "\n--------------------------\n";
}
void red_ybus(MatrixXd& bus_sol, MatrixXd& line , MatrixXd& mac_con, MatrixXd& load_con,double basmva)
{

    complex<double> jay(0, 1);

    int n_line = 14;  // number of lines
    int n_bus = 13;   // number of buses 

    int n = mac_con.rows(); // 4 based on the documents
    int nmot = 0 ; 
    int nig = 0; 
    
    int ngm = n + nmot;  
    int n_tot = ngm + nig;  //total number
    
    int nload = load_con.rows();
    MatrixXd J = load_con.col(0); 

    //----------------
    vector<Bus> buses = createBussesFromMatrix(bus_sol);   //makes it so it works in Y_Sparse ...
    NBus nBus(buses);
    vector<Line> lines= createLinesFromMatrix(line);
    //---------------
    
    MatrixXcd Y_d = Y_Sparse(&nBus , lines.data()); 

    MatrixXd V = bus_sol.col(1); 

    for(int li = 0; li < nload ; ++li){
        bus_sol((int)J(li) -1, 5) = (1 - load_con(li ,1) - load_con(li,3)) *  bus_sol((int)J(li) -1, 5);   
        bus_sol((int)J(li) -1, 6) = (1 - load_con(li ,2) - load_con(li,4)) *  bus_sol((int)J(li) -1 , 6);    
    }    
    
    MatrixXd gen_exist = MatrixXd::Zero(n_bus , 1);

    for (int li = 0; li < n_bus; ++li) {
        for(int index = 0; index < mac_con.rows() ; ++index){
            if (li == (int)mac_con(index, 1) -1){
                gen_exist(li ,0) = (int)mac_con(index, 0);   //this needs to be checked for sure ...
            }
        }
    }


    MatrixXd Pl = bus_sol.col(5);     // Pl (n_bus ,1)
    MatrixXd Ql = bus_sol.col(6);     // Ql (n_bus ,1)

    MatrixXd netgen = MatrixXd::Zero(0 ,1);

    for (int li = 0; li < n_bus; ++li) {
        if(gen_exist(li ,0) == 0) {    
            netgen.conservativeResize(netgen.rows() +1, NoChange);
            netgen(netgen.rows() -1  ,0) = li + 1;
            Pl(li,0) = Pl(li) - bus_sol(li ,3); // Pl = Pl - Pg ..
            Ql(li,0) = Ql(li) - bus_sol(li ,4);  // Ql = Ql - Qg ...
        }
    }

    MatrixXcd yl = MatrixXd::Zero(n_bus , n_bus);    

    for (int li = 0; li < n_bus; ++li) {
        yl(li,li) = ((Pl(li ,0) - (Ql(li, 0) * jay )) / (V(li) * V(li)));
    }

    Y_d = Y_d + yl;

    MatrixXd ra(n , 1);   // indexing ... (4 ,1)
    for(int i = 0; i < n;++i){
        ra(i ,0) = (mac_con(i ,4) * basmva) / mac_con(i ,2);
    }
    

    MatrixXd testxp = MatrixXd::Zero(n ,1);
    MatrixXd testxpp = MatrixXd::Ones(n ,1);

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


    MatrixXd Xd = MatrixXd::Zero(n ,1);

    if (txpp.size() != 0){
        for(int li = 0; li < txpp.size();++li){
            Xd(txpp[li]) = (mac_con(txpp[li] ,7) * basmva) / mac_con(txp[li] ,2);
        }
    }
    
    if (txp.size() != 0){
        for(int li = 0; li < txp.size();++li){
            Xd(txp[li]) = (mac_con(txp[li] ,6) * basmva) / mac_con(txp[li] ,2);
        }
    }
    
    
    MatrixXcd y = MatrixXcd::Zero(n ,1);

    for (int i = 0; i < n; ++i) {
        y(i ,0) = 1.0 / (ra(i ,0) + jay * Xd(i,0));
    }


    MatrixXd Jg(0 ,1);

    for (int li = 0; li < n_bus; ++li) {
        if ((gen_exist(li , 0) != 0)) {
            Jg.conservativeResize(Jg.rows() + 1, NoChange);
            Jg(Jg.rows()- 1, 0) = li +1; //bus numbers
        }
    }
    
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
  
    //------------------------
    MatrixXcd Y_b = MatrixXcd::Zero(n_tot ,n_bus);

    for (int li = 0; li < n_tot; ++li) {  // Loop over rows
        for (int lj = 0; lj < Jg.rows(); ++lj) {  // Loop over indices in Jg
            int col_idx = Jg(lj, 0) - 1;  
            Y_b(li, col_idx) = -Ymod(li, lj);  
        }
    }

    MatrixXcd m = perm * Ymod;


    for(int li = 0;li < Jg.rows(); ++li){
        for(int lj = 0;lj <Jg.rows();++lj){
            Y_d((int)Jg(li) -1,(int)Jg(lj) -1) += m(li, lj); 
        }
    }

    double motmax = 0;
    double igmax = 0;
   
    MatrixXcd Y_a = MatrixXcd::Zero(n_tot ,n_tot);
    for(int li = 0; li < n_tot  ; ++li){
        Y_a(li,li) = y(li ,0);
    }

    MatrixXcd Y_c = Y_b.transpose();
    
    if(nload == 0){

        MatrixXcd Y12 = (Y_d.inverse() * (-1)) * Y_c;
        MatrixXcd rec_V1 = Y12;
        MatrixXcd Y11 = (Y_b * Y12) + Y_a;
        MatrixXcd bus_order = bus_sol.col(0); //bus numbers or maybe col(0);

        //creating null matrixes ...
        //sizes need to be checked ...
        // MatrixXd Y12 = MatrixXd::Zero();
        // MatrixXd Y21 = MatrixXd::Zero();
        // MatrixXd Y22 = MatrixXd::Zero();
        // MatrixXd rec_V2 = MatrixXd::Zero();
    }

    else{

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
        
        MatrixXd p = MatrixXd::Zero(n_bus, n_bus);

        for (int li = 0; li < n_bus; ++li) {
            int order = static_cast<int>(bus_order(li, 0)) - 1;  // Subtract 1 to convert to zero-based index
            if (order >= 0 && order < n_bus) {  // Ensure the index is within bounds
                p(li, order) = 1;
            }
        }
        Y_b =  Y_b * p.transpose();
        Y_c =  p * Y_c;
        Y_d = (p * Y_d) * p.transpose();


        MatrixXcd Y_b1 = Y_b.block(0, 0, Y_b.rows(), nload);              // First nload columns
        MatrixXcd Y_b2 = Y_b.block(0, nload, Y_b.rows(), Y_b.cols() - nload); // Columns from nload to end



        MatrixXcd Y_c1 = Y_c.block(0, 0, nload, Y_c.cols());                  // Rows from 0 to nload-1
        MatrixXcd Y_c2 = Y_c.block(nload, 0, Y_c.rows() - nload, Y_c.cols()); // Rows from nload to end

  

        MatrixXcd Y_d1 = Y_d.block(0, 0, nload, Y_d.cols());                // Rows from 0 to nload-1
        MatrixXcd Y_d2 = Y_d.block(nload, 0, Y_d.rows() - nload, Y_d.cols()); // Rows from nload to end


        MatrixXcd Y_d11 = Y_d1.block(0, 0, Y_d1.rows(), nload);              // Columns from 0 to nload-1
        MatrixXcd Y_d12 = Y_d1.block(0, nload, Y_d1.rows(), Y_d1.cols() - nload); // Columns from nload to end

        MatrixXcd Y_d21 = Y_d2.block(0, 0, Y_d2.rows(), nload);              // Columns from 0 to nload-1
        MatrixXcd Y_d22 = Y_d2.block(0, nload, Y_d2.rows(), Y_d2.cols() - nload); // Columns from nload to end


        Eigen::MatrixXcd concatenated(Y_c2.rows(), Y_c2.cols() + Y_d21.cols());
        concatenated << Y_c2, Y_d21;


        MatrixXcd rec_V2 = (-1 * (Y_d22.inverse())) * (concatenated);
        
        MatrixXcd rec_V1 = rec_V2.block(0, 0, rec_V2.rows(), n_tot);
   
      
        int start_col = n_tot; // Starting column index
        int end_col = n_tot + nload; // Ending column index
        int block_width = end_col - start_col; // Calculate block width

        
        rec_V2 = rec_V2.block(0, start_col, rec_V2.rows(), block_width);
                

        MatrixXcd Y_11 = Y_a + (Y_b2 * rec_V1);
        MatrixXcd Y_12 = (Y_b2 * rec_V2) + Y_b1;
        MatrixXcd Y_21 = Y_c1 + (Y_d12* rec_V1);
        MatrixXcd Y_22 = Y_d11 + ( Y_d12* rec_V2);

        cout << "Y_11 is \n" << Y_11 << "\n";
        cout << "Y_12 is \n" << Y_12 << "\n";
        cout << "Y_21 is \n" << Y_21 << "\n";
        cout << "Y_22 is \n" << Y_22 << "\n";
        cout << "rec_v1 is \n" << rec_V1 << "\n";
        cout << "rec_v2 is \n" << rec_V2 << "\n";
        cout << "bus_order is \n" << bus_order << "\n";

        print_func(Y_11,Y_11.rows(),Y_11.cols());
        print_func(Y_12,Y_12.rows(),Y_12.cols());
        print_func(Y_21,Y_21.rows(),Y_21.cols());
        print_func(Y_22,Y_22.rows(),Y_22.cols());
        print_func(rec_V1,rec_V1.rows(),rec_V1.cols());
        print_func(rec_V2,rec_V2.rows(),rec_V2.cols());
    }
}