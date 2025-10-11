#include "../include/H_header.h"

using namespace std;

float Bus::Convert_deg_to_rad(float tmp_ang)
{
    float pi = 3.14159265359;
    return (tmp_ang * (pi / 180));
};

Bus::Bus(float _tmp_ang)
{
    tmp_ang=_tmp_ang;
};