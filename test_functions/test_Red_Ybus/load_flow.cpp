#include "H_header.h"

using namespace std;
using namespace Eigen;


void load_flow(MatrixXd bus, MatrixXd line, double tol, double iter_max, double acc ,string display ,double flag) {

    complex<double> jay(0.0 ,1.0);

    int nline = line.rows(); //line numbers
    int nbus = bus.rows(); //bus numbers
    int nlc = line.cols(); //number of line colmuns ... 
    int ncol = bus.cols();  //number of bus columns ...

    MatrixXd busCopy = bus;
    
    vector<Bus> busses = createBussesFromMatrix(bus);   //make it so it works in Y_Sparse ...
    NBus nBus(busses);
    vector<Line> lines= createLinesFromMatrix(line);
    
    double tap_it = 0;
    double tap_it_max = 10;
    double no_taps = 0;
    double mm_chk = 1;
    
    MatrixXd bus_no ;   //matrix for bus numbers ...
    MatrixXd V ;  //matrix for v
    MatrixXd ang ;  //ang matrix and turn them to radian ....
    MatrixXd Pg ; //matrix for Pg
    MatrixXd Qg ; //matrix for Qg
    MatrixXd Pl ; //matrix for Pl
    MatrixXd Ql ; //matrix fo10r Ql
    MatrixXd Gb ; //    ...
    MatrixXd Bb ; //    ...
    MatrixXd bus_type ;// ...
    MatrixXd qg_max ;
    MatrixXd qg_min ;
    MatrixXd volt_min ;
    MatrixXd volt_max ;

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

    int swing_index;
    MatrixXd delP, delQ, P, Q;

    delP.setZero();
    delQ.setZero();
    P.setZero();
    Q.setZero();
    
    int conv_flag;


    MatrixXcd Y;
    MatrixXd ang_red_1;
    MatrixXd volt_red_1;

    MatrixXd sw_bno_1;
    MatrixXd g_bno_1;


    int counter = 0;
    while(tap_it < tap_it_max && mm_chk == 1){

        tap_it ++;
        cout << "tap_it is : " << tap_it << "\n";
        
        Y = Y_Sparse(&nBus,lines.data());

        for(int i = 0; i < bus.rows() ;++i){
            if(bus(i ,9) == 1){
                swing_index = bus(i ,0);
            }
        }

        MatrixXd PQV_no(0 ,1);    // PQV_no matrix ... //bus_type >= 2
        for(int i =0;i <bus.rows();++i ){
            if(bus(i ,9) >= 2){
                PQV_no.conservativeResize(PQV_no.rows() +1, NoChange);
                PQV_no(PQV_no.rows() - 1, 0) = bus(i, 0);
            }
        }

        MatrixXd PQ_no(0 ,1);    // PQ_no matrix ...    //bus_type == 3
        for(int i =0;i <bus.rows();++i ){
            if(bus(i ,9) == 3){
                PQ_no.conservativeResize(PQ_no.rows() +1, NoChange);
                PQ_no(PQ_no.rows() - 1, 0) = bus(i, 0);
            }
        }

        MatrixXd gen_index(0 ,1);  // gen_index matrix ...    //bus_type == 2
        for(int i =0;i <bus.rows();++i ){
            if(bus(i ,9) == 2){
                gen_index.conservativeResize(gen_index.rows() +1,NoChange);
                gen_index(gen_index.rows() -1 , 0) = bus(i ,0);
            }
        }

        MatrixXd sw_bno = MatrixXd::Ones(nbus, 1);  // all ones ...
        for(int i = 0; i < nbus; ++i) {
            if(i == swing_index -1) {
                sw_bno(i, 0) = 0;  // if swing eq to zero ...
                break;
            }
        }   
        
        MatrixXd g_bno = MatrixXd::Ones(nbus, 1);  // all ones ..
        for(int i = 1; i < nbus; ++i) {
            for(int j = 0; j < gen_index.rows(); ++j) {
                if(i == gen_index(j, 0)) {
                    g_bno(i - 1, 0) = 0; //set that elemnt to zero
                    break; 
                }
            }
        }
        
        sw_bno_1 = sw_bno;
        g_bno_1 = g_bno;
        //-----------------------------
        int il_ang_red = PQV_no.rows();
        MatrixXd ang_red(il_ang_red ,nbus);
        ang_red.setZero();
        vector<int> ii_ang_red;

        for(int i = 0; i < il_ang_red ;++i){
            ii_ang_red.push_back(i);
        }

        for(int i = 0; i < il_ang_red;++i){
            int j = static_cast<int>(PQV_no(i,0)) -1;
            ang_red(i,j) = 1; 
        }

        ang_red_1 = ang_red;
        //----------------------------
        int il_volt_red = PQ_no.rows();
        MatrixXd volt_red(il_volt_red,nbus); 
        volt_red.setZero();
        vector<int> ii_volt_red;

        for(int i = 0; i < il_volt_red ;++i){
            ii_volt_red.push_back(i);
        }

        for(int i = 0; i < il_volt_red;++i){
            int j = static_cast<int>(PQ_no(i,0)) -1;
            volt_red(i,j) = 1; 
        }

        volt_red_1 = volt_red;

        //----------------------------
        int iter = 0; //for the inner loop
        calc(V, ang, Y, Pg, Qg, Pl, Ql, sw_bno, g_bno, tol, delP, delQ, P, Q, conv_flag);   // this will correctly update the delP , delQ ,P ,Q and conv_flag ...

        while(conv_flag == 1  && iter < iter_max){ 
            iter ++;
            cout << "iter is : " << iter << "\n";

            MatrixXd Jac = Form_Jac_1(V,ang,Y,ang_red,volt_red);

            MatrixXd red_delP = ang_red * delP;
            MatrixXd red_delQ = volt_red * delQ;
            MatrixXd vertical_concatenation(red_delP.rows() + red_delQ.rows(), 1);
            vertical_concatenation << red_delP, red_delQ;

            cout << "vertical is \n " << vertical_concatenation << "\n";
            
            MatrixXd temp = Jac.inverse() * vertical_concatenation;
            
            MatrixXd temp_1 = temp.block(0,0,PQV_no.size(),temp.cols());
            MatrixXd temp_2 = temp.block(PQV_no.size(),0,temp.rows()- PQV_no.size(),temp.cols());
            
            MatrixXd delAng = ang_red.transpose() * temp_1;
            MatrixXd delV = volt_red.transpose() * temp_2;
            
            V = V + (delV * acc);
            
            for(int i = 0 ;i < V.rows(); ++i ){
                V(i ,0) = max(V(i ,0),volt_min(i,0)); //should be V > volt_min
            }

            for(int i = 0 ; i < V.rows() ; ++i ){ 
                V(i ,0) = min(V(i ,0),volt_max(i,0)); // should be V < volt_max
            }

            ang = ang + (delAng * acc);

            calc(V, ang, Y, Pg, Qg, Pl, Ql, sw_bno, g_bno, tol, delP, delQ, P, Q, conv_flag); 
           
            for(int i = 0;i < bus.rows(); ++i){    // if bus_type == PV
                if(bus(i ,9) == 2){
                    Qg(i ,0) = Q(i ,0) + Ql(i ,0);
                }
            }
            
            int lim_flag = chq_lim(bus,Qg,Ql,qg_max,qg_min);     

            if(lim_flag == 1){
                cout << "Qg on the limit\n";
            }
        }

        if(conv_flag == 0){
            lftap(bus,V,volt_min,volt_max,line);
            // mm_chk = 0;
        }
        else{
            lftap(bus,V,volt_min,volt_max,line);          
        }
    }
    
    cout << "counter is : " << counter << "\n";
    
    if(tap_it == tap_it_max){
        cout << "tap iteration failed to converge after: " << tap_it << " iterations\n";
    }
    else{
        cout << "tap iterations : " << tap_it << "\n";
    }

    MatrixXd gen_idnex(0  ,1);
    for(int i = 0 ; i < bus.rows();++i){
        if(bus(i ,9) == 2){
            gen_idnex.conservativeResize(gen_idnex.rows() +1 , NoChange);
            gen_idnex(gen_idnex.rows() -1 ,0) = bus(i ,0);
        }
    }
    
    MatrixXd load_index(0 ,1);
    for(int i = 0 ; i < bus.rows();++i){
        if(bus(i ,9) ==3){
            load_index.conservativeResize(load_index.rows() +1 ,NoChange);
            load_index(load_index.rows() -1, 0) = bus(i ,0);
        }
    }

    MatrixXd gend_idx(0, 1);  

    for(int i = 0; i < bus.rows(); ++i) {
        if(bus(i, 9) != 2 && busCopy(i, 9) == 2) {
            gend_idx.conservativeResize(gend_idx.rows() + 1, NoChange);
            gend_idx(gend_idx.rows() - 1, 0) = bus(i, 0);
        }
    }
    

    for(int i = 0; i < bus.rows() ;++i){
        if(bus(i ,9) == 2){
            Qg(i,0) = Q(i ,0) + Ql(i ,0);
            Pg(i,0) = P(i ,0) + Pl(i ,0);
        }
    }
     
    MatrixXd Qlg(0, 1);  // Initialize Qlg with 0 rows and 1 column.
    
    if (gend_idx.rows() > 0) {
        for (int i = 0; i < gend_idx.rows(); ++i) {
            // Resize Qlg to add a new row
            Qlg.conservativeResize(Qlg.rows() + 1, NoChange);

            int idx = static_cast<int>(gend_idx(i, 0)) - 1;
            Qlg(Qlg.rows() - 1, 0) = Ql(idx, 0) - busCopy(idx, 6);
            Qg(idx, 0) = Qg(idx, 0) - Qlg(Qlg.rows() - 1, 0);
            Ql(idx, 0) = busCopy(idx, 6);
        }
    }
    

    for(int i = 0; i < bus.rows() ;++i){
        if(bus(i ,9) == 3){
            Pl(i ,0) = Pg(i ,0) - P(i ,0);
            Ql(i ,0) = Qg(i ,0) - Q(i ,0);
        }
    }

    Pg(swing_index -1,0) = P(swing_index -1, 0) + Pl(swing_index -1, 0);
    Qg(swing_index -1,0) = Q(swing_index -1, 0) + Ql(swing_index -1, 0); //this line exists in the matlab code but in the doc it's not mentioned
    
    //----------------------------------------

    MatrixXcd ang_complex = (ang.array() *jay).exp();
    MatrixXcd V_rect = V.array() * ang_complex.array();
    MatrixXcd VV = V_rect;
    
    MatrixXd tap_ratio(nline ,1); 
    
    for(int i = 0; i < nline;++i){
        if(line(i ,5) == 0){
            tap_ratio(i,0) = 1;
        }
        tap_ratio(i,0) = line(i ,5);
    }

    MatrixXd phase_shift = line.col(6);
    MatrixXcd phase_shift_complex = phase_shift.array() * (M_PI / 180.0) * jay;
    phase_shift_complex = phase_shift_complex.array().exp();
    MatrixXcd tps = tap_ratio.array() * phase_shift_complex.array(); // element by element multipication ..
    
    MatrixXd from_bus  = line.col(0);
    MatrixXd to_bus = line.col(1);
    MatrixXd r = line.col(2);
    MatrixXd rx = line.col(3);
    MatrixXd chrg = line.col(4);
    MatrixXcd z = r + (rx * jay);   
    MatrixXcd y = z.array().inverse();  

    MatrixXd i = from_bus;
    MatrixXd j = to_bus;

    MatrixXcd MW_s(line.rows() ,1);
    for(int k = 0; k < nline;k++){
        int from_idx = (int)i(k) - 1;  
        int to_idx = (int)j(k) - 1;  

        complex<double> x_1 = VV(from_idx);  // VV(from_int)
        complex<double> x_22 = tps(k) * VV(to_idx);  // tps .* VV(to_int)
        complex<double> x_21 = VV(from_idx) - x_22;  // VV(from_int) - tps .* VV(to_int)
        complex<double> x_23 = VV(from_idx) * jay * chrg(k) / 2.0;  // VV(from_int) .* (jay * chrg / 2)
        complex<double> x_2 = (x_21 * y(k)) + x_23;  // Combine above steps
        x_2 = conj(x_2);  // Take conjugate
        complex<double> x_3 = tps(k) * conj(tps(k));  // tps .* conj(tps)

        MW_s(k, 0) = x_1 * x_2 / x_3;  
    }
    
    MatrixXd P_s = MW_s.real();
    MatrixXd Q_s = MW_s.imag();

    MatrixXcd MW_r(line.rows() ,1);
    for(int k = 0; k < nline;k++){
        complex<double> x_1 = VV((int)j(k) -1);    //cast to int to make sure ....
        complex<double> x_2 = (((VV((int)j(k) - 1) -(VV((int)i(k) - 1))) / tps(k)) * y(k)) + (VV((int)j(k) -1) * jay * chrg(k) / 2.0);
        x_2 = conj(x_2);
        MW_r(k,0) = x_1 * x_2;
    }   
  

    MatrixXd P_r = MW_r.real();
    MatrixXd Q_r = MW_r.imag();

    double Q_loss = Q_r.sum() + Q_s.sum();
    double P_loss = P_r.sum() + P_s.sum();

    MatrixXd iline(line.rows() ,1);
    for (int i = 1;i <line.rows()+1;++i){
        iline(i -1 ,0) = i;
    }

    MatrixXd line_ffrom(nline ,5);
    line_ffrom << iline , from_bus , to_bus , P_s ,Q_s;

    MatrixXd line_fto(nline ,5);
    line_fto << iline , to_bus , from_bus , P_r ,Q_r;

    MatrixXd line_flow(2*nline ,5);
    line_flow <<line_ffrom,
                line_fto;

    MatrixXd line_sol = line;

    MatrixXd bus_sol(nbus,ncol);
    bus_sol << bus_no,V,ang.array() * (180.0 / M_PI), Pg , Qg,Pl,Ql,Gb,Bb, bus_type,qg_max,qg_min,bus.col(12),volt_max,volt_min;

    MatrixXd Jac = Form_Jac_1(V,ang,Y,ang_red_1,volt_red_1); 

    std::cout << "line_sol is \n" << line_sol << "\n";
    std::cout << "bus_sol is \n" << bus_sol << "\n"; 
    std::cout << "line_flow is \n" << line_flow << "\n";
    std::cout << "Jac is \n" << Jac << "\n";
}
