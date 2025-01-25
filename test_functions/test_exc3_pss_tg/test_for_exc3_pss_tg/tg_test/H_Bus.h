#ifndef H_Bus
#define H_Bus

#include<vector>

using namespace std;
enum busTypeEnum {Swing=1,PV=2,PQ=3};

class Bus
{
    public:
    float Bus_no;
    float V;
    float tmp_ang;
    float Pg;
    float Qg;
    float Pl;
    float Ql;
    float Gb;
    float Bb;
    float qg_max;
    float qg_min;
    float v_rate;
    float v_max;
    float v_min;
    
    Bus() : Bus_no(0), V(0), tmp_ang(0), Pg(0), Qg(0), Pl(0), Ql(0), Gb(0), Bb(0), 
            qg_max(0), qg_min(0), v_rate(0), v_max(0), v_min(0), busType(PQ) {}
    
    busTypeEnum busType;
    float Convert_deg_to_rad(float tmp_ang);
    float ang,teta;
    Bus (float _tmp_ang);
};
#endif