#include "MA27.h"
#include "MA57.h"
#include "linSolve.h"
#include <iostream>

using namespace std;

int main (int argc, char *argv[])
{
 
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
    
    double b[n];
    b[0] = 8; b[1] = 45.; b[2] = 31.; b[3] = 15.; b[4] = 17.;
    
    double* sollinSol;
    double* sollinSol2;
    /* ====== End Data ====== */
    
    /* ====== Test linSolve with MA27 ====== */
	linSolve<double*, double**,MA27> linSolveT(n, nz, A);
    /*
     * Here we set the vector type to be double* and the matrix type to be double**
     * Currently it only accepts dynamically allocated arrays, 
     * becasue of the implementation of MA27 and MA57.
     */
    
    linSolveT.Factorize();
    linSolveT.Solve(b);
    sollinSol = linSolveT.getSol();
    
    cout<<"Solution for Ax = b:"<<endl;
    cout<<"( "<<sollinSol[0];
    for (int i=1; i<n; i++)
    {
        cout<<", "<<sollinSol[i];
    }
    cout<<" )"<<endl;
    
    /*
     * Just the right hand side; no need to factorize the matirx again.
     */
    double b2[5] = {1,2,1,2,3};
    linSolveT.Solve(b2);
    sollinSol2 = linSolveT.getSol();
    
    cout<<"Solution for Ax = b2:"<<endl;
    cout<<"( "<<sollinSol2[0];
    for (int i=1; i<n; i++)
    {
        cout<<", "<<sollinSol2[i];
    }
    cout<<" )"<<endl;
    
    /* ====== End linSolve ====== */

    /* Release memory*/
    for (int i=0; i<5; i++)
    {
        delete[] A[i];
    }
    delete[] A;
    
    return 0;
}
