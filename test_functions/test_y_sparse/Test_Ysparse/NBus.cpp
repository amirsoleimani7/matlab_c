#include "H_header.h"

using namespace std;

NBus::NBus(vector<Bus> _N_bus)
{
    N_bus = _N_bus;
};

void NBus::Set_sw_bno(vector<Bus> N_bus)
{
    for(int i=0;i<N_bus.size();i++)
    {
        if(N_bus[i].busType != Swing)
        {
            sw_bno[i]=1;
        };
    };
};

void NBus::Set_g_bno(vector<Bus> N_bus)
{
    for(int i=0;i<N_bus.size();i++)
    {
        if(N_bus[i].busType != PV)
        {
             g_bno[i]=1;
        };
    };
    
};

void NBus::Set_SIndex_PQN_SB_GIndex(vector<Bus> N_bus)
{
    busTypeEnum type;
    for(int i=0;i<N_bus.size();i++)
    {
        switch ((N_bus[i].busType))
        {
        case Swing:
            Swing_index[i]=1;
            SB[i]=1;
            break;
        case PQ :
            PQ_No[i]=1;
            break;
        case PV :
            gen_index[i]=1;
            break;
        default:
            break;
        };
    };
}

void NBus::Set_PQV_No(vector<Bus> N_bus)
{
        for(int i=0;i<N_bus.size();i++)
        {
            if(N_bus[i].busType == PV && N_bus[i].busType==PQ)
        {
             PQV_No[i]=1;
        };
        }
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



