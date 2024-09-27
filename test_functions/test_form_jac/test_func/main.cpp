
// #include"H_header.h"
#include"../hdr/Y_Sparse.h"

int main()
{
    NBus *NBusObj  ;
    Line* lineArray  ;
    MatrixXf c_from ;
    MatrixXf c_to;
    Y_Sparse(NBusObj  , lineArray  , c_from , c_to) ;
    return 0 ;
}