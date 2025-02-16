#include "../include/H_header.h"

using namespace std;
using namespace Eigen;


void print_matrix(MatrixXcd mat,double flag){
    cout << "\n----------------------\n";
    if(flag == 0){
        for(int i = 0; i < mat.rows();++i ){
            for(int j  = 0; j < mat.cols();++j ){
                cout << mat(i ,j).real() << ", " ;
            }
            cout << "\n";
        }
    }
    else{
        for(int i = 0; i < mat.rows();++i ){
            for(int j  = 0; j < mat.cols();++j ){
                cout << mat(i ,j).imag() << " , " ;
            }
            cout << "\n";
        }
    }
    cout << "\n----------------------\n";
}

void y_switch(MatrixXd& bus, MatrixXd& line,MatrixXd& load_con, MatrixXd& mac_con, MatrixXd& sw_con) {


    int nload = load_con.rows();
    double basmva = 100.0;

    MatrixXcd Y_gprf,Y_gncprf,Y_ncgprf,Y_ncprf,V_rgprf,V_rncprf;
    MatrixXd boprf;

    cout << "pre fault\n";
    cout << "bus is \n" << bus << "\n";
    cout << "line  is \n" << line << "\n";

    red_ybus(bus, line, mac_con, load_con, basmva, Y_gprf, Y_gncprf, Y_ncgprf, Y_ncprf, V_rgprf, V_rncprf, boprf);
    
    MatrixXd bus_intprf = bus.col(0);
    cout << "bus_intprf is \n" << bus_intprf << "\n";
    int n_bus = bus.rows(); 

    cout << "Y_gprf is \n" << Y_gprf << "\n";
    print_matrix(Y_gprf,0);
    print_matrix(Y_gprf,1);
    cout << "Y_gncprf is \n" << Y_gncprf << "\n";
    print_matrix(Y_gncprf,0);
    print_matrix(Y_gncprf,1);
    cout << "Y_ncgprf is \n" << Y_ncgprf << "\n";
    print_matrix(Y_ncgprf,0);
    print_matrix(Y_ncgprf,1);
    cout << "Y_ncprf is \n" << Y_ncprf << "\n";
    print_matrix(Y_ncprf,0);
    print_matrix(Y_ncprf,1);
    cout << "V_rgprf is \n" << V_rgprf << "\n";
    print_matrix(V_rgprf,0);
    print_matrix(V_rgprf,1);
    cout << "V_rncprf is \n" << V_rncprf << "\n";
    print_matrix(V_rncprf,0);
    print_matrix(V_rncprf,1);

    cout << "boprf is \n" << boprf << "\n";
    
    MatrixXd bus_f = bus;
    MatrixXd line_f = line;


    int f_nearbus = sw_con(1 ,1); /* sw_con(2 ,2)*/
    int f_farbus = sw_con(1 ,2); /*sw_con(2 ,3)*/

    int f_type =  sw_con(1 ,5);  /* sw_con(2 ,6) */  // Set based on your switching conditions
    cout << "f_type is : " << f_type << "\n ";

    double bf, xf;
     
    vector<int> bus_idx;

    for (int li = 0; li < bus_f.rows(); ++li) {
        if (bus_f(li ,0) == f_nearbus) {
            bus_idx.push_back(li);
        }
    }

    vector<int> line_idx;

    for (int li = 0; li < line_f.rows(); ++li) {
        if ((line_f(li, 0) == f_nearbus && line_f(li , 1) == f_farbus)){
            line_idx.push_back(li);
        }

        if (line_f(li ,1) == f_nearbus && line_f(li, 0) == f_farbus){
            line_idx.push_back(li);
        }
    }
    
    std::cout << "bus_idx is \n";
    for(int i = 0 ;i < bus_idx.size() ;++i){
        std::cout << bus_idx[i] << " ";
    }

    std::cout << "\n";

    std::cout << "line_idx is \n";
    for(int i = 0 ;i < line_idx.size() ;++i){
        std::cout << line_idx[i] << " ";
    }
    
    std::cout << "\n";

    cout << "f_type is : " << f_type << "\n ";
    
    if (f_type < 4 || f_type == 7) {
        if (bus_idx.empty()) {
            std::cout << "Faulted bus not specified correctly; bus_idx not found.\n";
        } else {
            // For fault types 0 to 3, handle bf calculations
            if (f_type == 0 || f_type == 7) {
                bf = 1.0e7; // Three-phase fault
            } else if (f_type == 1) {
                xf = (sw_con(1, 3) * sw_con(1, 4)) / (sw_con(1, 3) + sw_con(1, 4));
                xf = std::max(xf, 1e-7);
                bf = 1.0 / xf;
            } else if (f_type == 2) {
                xf = sw_con(1, 3) + sw_con(1, 4);
                xf = std::max(xf, 1e-7);
                bf = 1.0 / xf;
            } else if (f_type == 3) {
                xf = sw_con(1, 3);
                xf = std::max(xf, 1e-7);
                bf = 1.0 / xf;
            }

            bus_f(bus_idx[0], 8) = -bf; 
        }
    }

    if (f_type == 4) {
        if (line_idx.empty()) {
            std::cout << "Faulted line not specified correctly; line_idx not found.\n";
        } else {
            line_f(line_idx[0], 3) = 1.0e7; // Making line reactance infinite
        }
    }

    if (f_type == 5) {
        if (bus_idx.empty()) {
            std::cout << "Faulted bus not specified correctly; bus_idx not found.\n";
        } else {
            bus_f(bus_idx[0], 5) = 0.0; // Setting load to 0
            bus_f(bus_idx[0], 6) = 0.0; // Setting generation to 0
        }
    }

    if (f_type == 6) {
        if (bus_idx.empty()) {
            std::cout << "Faulted bus not specified correctly; bus_idx not found.\n";
        }
    }

    MatrixXcd Y_gf, Y_gncf, Y_ncgf, Y_ncf, V_rgf, V_rncf;
    MatrixXd bof;
    cout << "on fualt\n";
    
    cout << "bus_f \n" << bus_f << "\n";
    cout << "line_f \n" << line_f << "\n";

    red_ybus(bus_f, line_f, mac_con, load_con, basmva, Y_gf, Y_gncf, Y_ncgf, Y_ncf, V_rgf, V_rncf, bof);
    MatrixXd bus_intf  = bus.col(0);
    cout << "Y_gf is \n" << Y_gf << "\n";
    print_matrix(Y_gf,0);
    print_matrix(Y_gf,1);

    cout << "Y_gncf is \n" << Y_gncf << "\n";
    print_matrix(Y_gncf,0);
    print_matrix(Y_gncf,1);
    cout << "Y_ncgf is \n" << Y_ncgf << "\n";
    print_matrix(Y_ncgf,0);
    print_matrix(Y_ncgf,1);
    
    cout << "Y_ncf is \n" << Y_ncf << "\n";
    print_matrix(Y_ncf,0);
    print_matrix(Y_ncf,1);
    
    cout << "V_rgf is \n" << V_rgf << "\n";

    print_matrix(V_rgf,0);
    print_matrix(V_rgf,1);

    cout << "V_rncf is \n" << V_rncf << "\n";
    print_matrix(V_rncf,0);
    print_matrix(V_rncf,1);
    cout << "bof is \n" << bof << "\n";

    print_matrix(bof,0);
    print_matrix(bof,1);
    cout << "bus_intf is \n" << bus_intf << "\n"; 


    MatrixXd bus_pf1 = bus;
    MatrixXd line_pf1 = line;
    
    MatrixXcd Y_gpf1, Y_gncpf1, Y_ncgpf1, Y_ncpf1, V_rgpf1, V_rncpf1;
    MatrixXd bopf1,bus_intpf1;
    int dlpf1;
    int max_pf1b;

    if (f_type < 4) {

        bus_pf1 = bus;
        line_pf1 = line;

        if(line_idx.empty()){
            cout << "Faulted bus not specified correctly \n line_idx not found \n";
        }

        else{

            line_pf1(line_idx[0] ,3) = 1.0e7;  // rx set to infinite ...

            int new_bus = bus.col(0).maxCoeff() + 10;   //max(bus_num) +10
            max_pf1b = bus.rows() + 1; //one more than we have  ..

            bus_pf1.conservativeResize(bus_pf1.rows() + 1, bus_pf1.cols());
            
            bus_pf1(max_pf1b -1, 0) = new_bus;
            bus_pf1(max_pf1b -1, 1) = 1;
            bus_pf1(max_pf1b -1, 8) = bus_f(bus_idx[0], 8);
            bus_pf1(max_pf1b -1, 9) = 3;


            dlpf1 = line_f.rows() +1;

            line_pf1.conservativeResize(line_pf1.rows() + 1, line_pf1.cols());

            line_pf1(dlpf1 -1, 0) = new_bus;
            line_pf1(dlpf1 -1, 1) = f_farbus;
            line_pf1(dlpf1 -1, 2) = line(line_idx[0],2);
            line_pf1(dlpf1 -1, 3) = line(line_idx[0],3);
            line_pf1(dlpf1 -1, 4) = line(line_idx[0],4);
            line_pf1(dlpf1 -1, 5) = line(line_idx[0],5);
            red_ybus(bus_pf1, line_pf1, mac_con, load_con, basmva, Y_gpf1, Y_gncpf1, Y_ncgpf1, Y_ncpf1, V_rgpf1, V_rncpf1, bopf1);
        }

    } else if (f_type == 4 || f_type == 5 || f_type == 6) {
        
        bus_pf1 = bus_f;
        line_pf1 = line_f;
        Y_gpf1 = Y_gf;
        Y_gncpf1 = Y_gncf;
        Y_ncgpf1 = Y_ncgf;
        Y_ncpf1 = Y_ncf;
        V_rgpf1 = V_rgf;
        V_rncpf1 = V_rncf;
        bopf1 = bof;

    } else if (f_type == 7) {

        bus_pf1 = bus;
        line_pf1 = line;
        Y_gpf1 = Y_gprf;
        Y_gncpf1 = Y_gncprf;
        Y_ncgpf1 = Y_ncgprf;
        Y_ncpf1 = Y_ncprf;
        V_rgpf1 = V_rgprf;
        V_rncpf1 = V_rncprf;
        bopf1 = boprf;
        bus_intpf1 = boprf;
        cout << "post_fault 1\n";       
        cout << "Y_gpf1 is \n" << Y_gpf1 << "\n";
        print_matrix(Y_gpf1,0);
        print_matrix(Y_gpf1,1);

        cout << "Y_gncpf1 is \n" << Y_gncpf1 << "\n";
        print_matrix(Y_gncpf1,0);
        print_matrix(Y_gncpf1,1);


        cout << "Y_ncgpf1 is \n" << Y_ncgpf1 << "\n";
        print_matrix(Y_ncgpf1,0);
        print_matrix(Y_ncgpf1,1);
 
        cout << "Y_ncpf1 is \n" << Y_ncpf1 << "\n";
        print_matrix(Y_ncpf1,0);
        print_matrix(Y_ncpf1,1);
 
        cout << "V_rgpf1 is \n" << V_rgpf1 << "\n";
        
        print_matrix(V_rgpf1,0);
        print_matrix(V_rgpf1,1);

        cout << "V_rncpf1 is \n" << V_rncpf1 << "\n";
        print_matrix(V_rncpf1,0);
        print_matrix(V_rncpf1,1);

        cout << "bopf1 is \n" << bopf1 << "\n";
        cout << "bus_intpf1 \n" << bus_intpf1 << "\n";

    }

    MatrixXd bus_pf2;
    MatrixXd line_pf2;
    
    MatrixXcd Y_gpf2, Y_gncpf2, Y_ncgpf2, Y_ncpf2, V_rgpf2, V_rncpf2;
    MatrixXd bopf2,bus_intpf2;

    if (f_type < 4) {
        line_pf2 = line_pf1;
        bus_pf2 = bus_pf1;
        line_pf2(dlpf1 -1, 3 ) = 1.0e7;
        bus_pf2(max_pf1b -1 ,8) = 0;
        red_ybus(bus_pf2, line_pf2, mac_con, load_con, basmva, Y_gpf2, Y_gncpf2, Y_ncgpf2, Y_ncpf2, V_rgpf2, V_rncpf2, bopf2);
    
    } else {

        bus_pf2 = bus_pf1;
        line_pf2 = line_pf1;
        Y_gpf2 = Y_gpf1;
        Y_gncpf2 = Y_gncpf1;
        Y_ncgpf2 = Y_ncgpf1;
        Y_ncpf2 = Y_ncpf1;
        V_rgpf2 = V_rgpf1;
        V_rncpf2 = V_rncpf1;
        bopf2 = bopf1;
        bus_intpf2 = bus_intpf1;
        
        cout << "post_fault 2\n";       
        cout << "Y_gpf2 is \n" << Y_gpf2 << "\n";
        print_matrix(Y_gpf2 ,0);
        print_matrix(Y_gpf2 ,1);

        cout << "Y_gncpf2 is \n" << Y_gncpf2 << "\n";
        print_matrix(Y_gncpf2 ,0);
        print_matrix(Y_gncpf2 ,1);
        
        cout << "Y_ncgpf2 is \n" << Y_ncgpf2 << "\n";
        print_matrix(Y_ncgpf2 ,0);
        print_matrix(Y_ncgpf2 ,1);
        cout << "Y_ncpf2 is \n" << Y_ncpf2 << "\n";
        print_matrix(Y_ncpf2 ,0);
        print_matrix(Y_ncpf2 ,1);
        cout << "V_rgpf2 is \n" << V_rgpf2 << "\n";
        
        print_matrix(V_rgpf2 ,0);
        print_matrix(V_rgpf2 ,1);
        cout << "V_rncpf2 is \n" << V_rncpf2 << "\n";
        print_matrix(V_rncpf2 ,0);
        print_matrix(V_rncpf2,1); 
        cout << "bopf2 is \n" << bopf2 << "\n";
        cout << "bus_intpf2 is \n" << bus_intpf2 << "\n"; 
    }
}
