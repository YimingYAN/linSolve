#include "include/cma27.h"
#include "include/cma57.h"
#include <cmath>
#include <iostream>

using namespace std;

int main (int argc, char *argv[])
{
    cout<<"Test cma27.h... "<<endl;
    
    /* ====== Begin Data ====== */
    double A[5][5];
    for (int i = 0; i<5; i++)
    {
        for (int j=0; j<5; j++) {
            A[i][j] = 0.0;
        }
    }
    A[0][0] = 2; A[0][1] = 3;
    A[1][0] = 3; A[1][2] = 4; A[1][4] = 6;
    A[2][1] = 4; A[2][2] = 1; A[2][3] = 5;
    A[3][2] = 5;
    A[4][1] = 6; A[4][4] = 1;
    
    double rhs[5] = {8., 45., 31., 15., 17.};
    /* ====== End Data ====== */
    
    /* ====== Begin Vars for MA27 ====== */
    int icntl[30];
    double cntl[5];
    int n  = 5;
    int nz = 7;
    int liw = 40;
    int la = 30;
    
    int irn[nz];
    int icn[nz];
    
    int iw[liw];
    int ikeep[3*n];
    int iw1[n];
    int nsteps;
    int iflag = 0;
    int info[20];
    double ops;
    
    double a[la];
    int maxfrt;
    
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
    /* ====== End Vars for MA27 ====== */
    
    /* ====== Begin MA27 ====== */
    // initialize
    ma27id_(icntl, cntl);
    icntl[2] = 2;
    
    cout<< "Run MA27D..."<<endl;
    cout<<" ======= ======= ======= "<<endl;
    
    
    // analyze
    ma27ad_(&n, &nz, irn, icn, iw, &liw, ikeep, iw1, &nsteps,
            &iflag, icntl, cntl, info, &ops);
    
    // factorize
    ma27bd_(&n, &nz, irn, icn, a, &la, iw, &liw,
            ikeep,  &nsteps, &maxfrt, iw1,
            icntl,  cntl, info);
    
    // solve
    double w[maxfrt];
    ma27cd_(&n, a, &la, iw, &liw, w, &maxfrt, rhs, iw1,
            &nsteps, icntl, info);
    /* ====== End MA27 ====== */
    
    /* ====== Begin Vars for MA57 ====== */
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
    counter = 0;
    for (int i=0; i<nz; i++)
    {
        for (int j=i; j<n; j++)
        {
            if (fabs(A[i][j]) > 1e-32)
            {
                a[counter] = A[i][j];
                counter++;
            }
        }
    }
    rhs[0] = 8; rhs[1] = 45.; rhs[2] = 31.; rhs[3] = 15.; rhs[4] = 17.;
    
    /* ====== End Vars for MA57 ====== */
    
    /* ====== Begin MA57 ====== */
    // initialize
    ma57id_(cntl57, icntl57);
    icntl57[4] = 4;
    
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
    
    return 0;
}
