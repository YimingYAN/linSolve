#include "cma27.h"
#include "cma57.h"
#include <iostream>

using namespace std;

int main (int argc, char *argv[])
{
    cout<<"Test cma27.h... "<<endl;
    
    /* ====== Begin Data ====== */
    int n  = 5;
    int nz = 7;
    
    
    double** A;
    A = new double* [n];
    for (int i=0; i<n; i++)
    {
        A[i] = new double[n];
    }
    
    A[0][0] = 2; A[0][1] = 3;
    A[1][0] = 3; A[1][2] = 4; A[1][4] = 6;
    A[2][1] = 4; A[2][2] = 1; A[2][3] = 5;
    A[3][2] = 5;
    A[4][1] = 6; A[4][4] = 1;
    
    double rhs[n];
    rhs[0] = 8; rhs[1] = 45.; rhs[2] = 31.; rhs[3] = 15.; rhs[4] = 17.;
    
    double* sol27;
    double* sol57;
    /* ====== End Data ====== */
    
    
    /* ====== Begin MA27 ====== */
    cma27 cma27(n, nz, A);
    cma27.Initialize();
    cma27.Analyze();
    cma27.Factorize(A);
    cma27.Solve(rhs);
    sol27 = cma27.getSol();
    cout<<"Solution from MA27:"<<endl;
    for (int i=0; i<n; i++)
    {
        cout<<"\t"<<sol27[i]<<endl;
    }
    /* ====== End MA27 ====== */
    
    
    /* ====== Begin MA57 ====== */
    cout<<"Test cma57.h... "<<endl;
    
    cma57 cma57(n,nz, A);
    cma57.Initialize();
    cma57.Analyze();
    cma57.Factorize();
    cma57.Solve(rhs);
    sol57 = cma57.getSol();
    
    cout<<"Solution from MA57:"<<endl;
    for (int i=0; i<n; i++)
    {
        cout<<"\t"<<sol57[i]<<endl;
    }
    
    /* ====== End MA57 ====== */
    
    /* Release memory*/
    for (int i=0; i<5; i++)
    {
        delete[] A[i];
    }
    delete[] A;
    
    return 0;
}
