#include "../include/H_header.h"

using namespace Eigen;
using namespace std;


void lftap(MatrixXd& bus,MatrixXd& V,MatrixXd& volt_min ,MatrixXd& volt_max, MatrixXd& line)
{
    cout << "\n---in lftap---\n";
    MatrixXd min_v_index(0 ,1);
    MatrixXd max_v_index(0 ,1);


    for(int i = 0;i < V.rows();++i){
        if (V(i ,0) <= volt_min(i ,0)){ //if v_min >= V
            min_v_index.conservativeResize(min_v_index.rows()+1 ,NoChange);
            min_v_index(min_v_index.rows() -1, 0) = bus(i ,0);
        }
        if (V(i ,0) >= volt_max(i ,0)){
            max_v_index.conservativeResize(max_v_index.rows() +1 ,NoChange);
            max_v_index(max_v_index.rows() -1, 0) = bus(i ,0);
        }
    }
    double tmp_for_v_max;
    double tap_for_v_max;
    for(int i = 0; i < max_v_index.rows(); ++i){
        for(int k = 0; k < line.rows();++k){
            if(line(k ,1) == max_v_index(i ,0)){ //if line[k].to_bus == index of max_v_index 
                if(line(k ,7) != 0){
                    cout << "voltage high changing tap on line\n";
                    
                    double v_error = V((int)max_v_index(i ,0) -1 ,0) - volt_max((int)max_v_index(i ,0) -1 ,0); //v[index] - volt_max[index]
                    tmp_for_v_max = v_error / volt_max((int)max_v_index(i ,0) -1 ,0);

                    if(tmp_for_v_max < line(k ,9)){
                        tap_for_v_max = line(k ,9) + line(k,5);
                        if(tap_for_v_max < line(k,8)){
                            tap_for_v_max = line(k ,8);
                        }
                        if(tap_for_v_max > line(k ,7)){
                            tap_for_v_max = line(k ,7);
                        }
                        line(k ,5) = tap_for_v_max;
                    }
                    else{

                        tap_for_v_max = (ceil(((line(k ,5) + tmp_for_v_max) - line(k ,8)) / line(k ,9)) * line(k ,9)) + line(k ,8);                        
                        if(tap_for_v_max < line(k,8)){
                            tap_for_v_max = line(k ,8);
                        }
                        if(tap_for_v_max > line(k ,7)){
                            tap_for_v_max = line(k ,7);
                        }   
                        line(k ,5) = tap_for_v_max;
                    }
                }
            }
        }
    }

    double tmp_for_v_min;
    double tap_for_v_min;

    for(int i = 0; i < min_v_index.rows(); ++i){
        for(int k = 0; k < line.rows();++k){
            if(line(k ,1) == min_v_index(i ,0)){ //if line[k].to_bus == index of max_v_index 
                if(line(k ,7) != 0){
                    cout << "voltage low changing tap on line\n";
                    double v_error =volt_min((int)min_v_index(i ,0) -1 , 0) -  V((int)min_v_index(i ,0) -1 ,0); 
                    tmp_for_v_min = v_error / volt_min((int)min_v_index(i ,0) -1 ,0);
                    
                    if(tmp_for_v_min < line(k ,9)){
                        tap_for_v_min = line(k,5) - line(k ,9) ;
                        if(tap_for_v_min < line(k,8)){
                            tap_for_v_min = line(k ,8);
                        }
                        if(tap_for_v_min > line(k ,7)){
                            tap_for_v_min = line(k ,7);
                        }
                        line(k ,5) = tap_for_v_min;
                        
                    }

                    else{
                        tap_for_v_min = (floor(((line(k ,5) + tmp_for_v_min) - line(k ,8)) / line(k ,9)) * line(k ,9)) + line(k ,8);
                        
                        if(tap_for_v_min < line(k,8)){
                            tap_for_v_min = line(k ,8);
                        }
                        if(tap_for_v_min > line(k ,7)){
                            tap_for_v_min = line(k ,7);
                        }
                        line(k ,5) = tap_for_v_min;
                    }
                }
            }
        }
    }
    cout << "\n---out lftap---\n";

}
