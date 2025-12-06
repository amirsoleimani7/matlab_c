#ifndef H_NBus
#define H_NBus

// #include <eigen3/Eigen/Core>
#include "../third_party/Eigen/Core"

#include "H_Bus.h"
#include <vector>
using namespace std;
using namespace Eigen;

#define N 13

class NBus
{
    public:
    vector <Bus> N_bus;
    vector <float> sw_bno;
    vector <float> g_bno;
    vector <float> Swing_index;
    vector <float> PQV_No;
    vector <float> PQ_No;
    vector <float> gen_index;
    vector <float> SB;
    public:
    VectorXd getGbArray() ;
    VectorXd getBbArray() ;
    NBus (vector<Bus> _N_bus);
};



#endif