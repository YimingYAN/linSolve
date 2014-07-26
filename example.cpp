#include "cma27.h"
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
    
    return 0;
}
