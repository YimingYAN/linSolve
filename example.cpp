#include "include/cma27.h"
#include "include/cma57.h"
#include <cmath>
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
    
    for (int i = 0; i<n; i++)
    {
        for (int j=0; j<n; j++) {
            A[i][j] = 0.0;
        }
    }
    A[0][0] = 2; A[0][1] = 3;
    A[1][0] = 3; A[1][2] = 4; A[1][4] = 6;
    A[2][1] = 4; A[2][2] = 1; A[2][3] = 5;
    A[3][2] = 5;
    A[4][1] = 6; A[4][4] = 1;
    
    double rhs[n];
    rhs[0] = 8; rhs[1] = 45.; rhs[2] = 31.; rhs[3] = 15.; rhs[4] = 17.;
    
    double* sol;
    /* ====== End Data ====== */
    
    
    /* ====== Begin MA27 ====== */
    cma27 cma27(n, nz, A);
    cma27.Initialize();
    cma27.Analyze();
    cma27.Factorize(A);
    cma27.Solve(rhs);
    sol = cma27.getSol();
    cout<< "Solution: "<<endl;
    for (int i=0; i<n; i++)
    {
        cout<<"\t"<<sol[i]<<endl;
    }
    /* ====== End MA27 ====== */

    /* ====== Begin Vars for MA57 ====== */
    int la = 30;
    double a[la];
    
    
    int irn[nz];
    int icn[nz];
    
    int liw = 40;
    int iw[liw];

    int icntl57[20];
    double cntl57[5];
    int lkeep57 = 100;
    int keep57[lkeep57];
    int iwork57[5*n];
    int info57[40];
    double rinfo57[20];
    int lfact57 = 1000;
    double fact57[lfact57];
    int lifact57 = 500;
    int ifact57[lifact57];
    int nrhs57 = 1, lrhs57 = 5, lw57 = 40, job57 = 1;
    double w57[lw57];
    
    // reset a and rhs
    int counter = 0;
    for (int i=0; i<nz; i++)
    {
        for (int j=i; j<n; j++)
        {
            if (fabs(A[i][j]) > 1e-32)
            {
                irn[counter] = i+1; // fortran index
                icn[counter] = j+1; // start from 1
                a[counter] = A[i][j];
                
                counter++;
            }
        }
    }
    
    /* ====== End Vars for MA57 ====== */
    
    /* ====== Begin MA57 ====== */
    // initialize
    ma57id_(cntl57, icntl57);
    //icntl57[4] = 4;
    
    cout<< "Run MA57D..."<<endl;
    cout<<" ======= ======= ======= "<<endl;
    
    
    // analyze
    ma57ad_(&n, &nz, irn, icn, &lkeep57, keep57, iw,
            icntl57, info57, rinfo57);
    
    // factorize
    ma57bd_(&n, &nz, a, fact57, &lfact57, ifact57, &lifact57, &lkeep57,
            keep57, iw, icntl57, cntl57, info57, rinfo57);
    
    // solve
    ma57cd_(&job57, &n, fact57, &lfact57, ifact57, &lifact57, &nrhs57, rhs,
            &lrhs57, w57, &lw57, iw, icntl57, info57);
    
    /* ====== End MA57 ====== */
    
    /* Release memory*/
    for (int i=0; i<5; i++)
    {
        delete[] A[i];
    }
    delete[] A;
    
    return 0;
}
