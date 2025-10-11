#include "../include/H_header.h"

using namespace std;

NBus::NBus(vector<Bus> _N_bus)
{
    N_bus = _N_bus;
};

VectorXd NBus::getGbArray()
{
    VectorXd resault(N) ; //this is wrong(need to initialize the vector first)
    for(int i=0 ; i<N ; i++)
    {
        resault(i) = N_bus[i].Gb ;
    }
    return resault ;
}

VectorXd NBus::getBbArray()
{
    VectorXd resault(N) ; // this is good 
    for(int i=0 ; i<N ; i++)
    {
        resault(i) = N_bus[i].Bb ;
    }
    return resault ;
}



