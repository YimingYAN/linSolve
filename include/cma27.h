/*
* Header file for cma27
* Created by Yiming Yan 
* 25 July 2014
*/
#ifndef maSolver_cma27_h
#define maSolver_cma27_h

#include <cmath>

class cma27
{
public:
    cma27();
    cma27(const int n, const int nz, double** A);
    
    void Initialize();
    void Analyze();
    void Factorize(double** A);
    void Solve(double* rhs);
    /*
     *rhs      - right hand side of the linear system (b in Ax=b);
     */
    
    double* getSol();
protected:
    int n;              // order of matrix, namely number of rows or cols
    int nz;             // number of nonzeros entries
    int icntl[30];      // integer array of length 30; integer control values
    double cntl[5];     // double array of length 5; double control values
    
    int* irn;           // row index of input
    int* icn;           // col index of input
    
    int liw;            // length of iw; at least 2*NZ+3*N+1 (or NZ+3*N+1 if the pivot order is specified in ikeep)
    int* iw;            // integer workspace of length liw
    int* ikeep;         // integer array of 3*n; pivot sequence
    int* iw1;           // integer workspace array of length n
    int nsteps;         // integer, to be set by ma27
    int iflag;          // integer; 0 if pivot order chosen automatically; 1 if the pivot order set by ikeep
    int info[20];       // integer array of length 20
    double ops;         // double, operations count
    
    double* factor;     // data array of length la;
    int la;             // length of a
    int maxfrt;         // integer, to be set by ma27
    
    double* sol;         // double array of length n; holds the solution
};

#ifdef __cplusplus
extern "C" {
#endif
    extern void ma27id_(int icntl[30], double cntl[5]);
    /* 
     *  MA27ID_ C interface for fortran routine MA27ID (Initialize)
     */
    
    extern void ma27ad_(int* n, int* nz, int* irn, int* icn, int iw[],
                        int* liw, int* ikeep, int* iw1, int* nsteps,
                        int* iflag, int icntl[30], double cntl[5],
                        int info[20], double* ops );
    /* 
     * MA27AD_ C interface for fortran routine MA27AD (Analyze)
     */
    
    extern void ma27bd_(int* n, int* nz, int* irn, int* icn,
                   double* a, int* la, int iw[], int* liw,
                   int* ikeep, int* nsteps, int* maxfrt, int* iw1,
                   int icntl[30], double cntl[5], int info[20]);
    /* 
     * MA27BD_ C interface for fortran routine MA27BD (Factorize)
     */
    
    extern void ma27cd_(int* n, double* a, int* la, int iw[], int* liw,
                       double* w, int* maxfrt, double* rhs, int* iw1,
                       int* nsteps, int icntl[30], int info[20]);
    /* 
     * MA27CD_ C interface for fortran routine MA27CD (Solve)
    */
#ifdef __cplusplus
}
#endif

cma27::cma27(){};

cma27::cma27(const int i_n, const int i_nz, double** A)
{
    n   = i_n;
    nz  = i_nz;
    liw = 3*(n+nz);
    iflag = 0;
    
    
    irn = new int[nz];
    icn = new int[nz];
    
    iw = new int[liw];
    ikeep = new int[3*n+3*nz];
    iw1 = new int[n];
    
    int counter = 0;
    for (int i=0; i<nz; i++)
    {
        for (int j=i; j<n; j++)
        {
            if (fabs(A[i][j]) > 1e-5)
            {
                irn[counter] = i+1; // fortran index
                icn[counter] = j+1; // start from 1
                
                counter++;
            }
        }
    }

}

void cma27::Initialize()
{
    ma27id_(icntl, cntl);
    icntl[2] = 2;
}

void cma27::Analyze()
{
    ma27ad_(&n, &nz, irn, icn, iw, &liw, ikeep, iw1, &nsteps,
            &iflag, icntl, cntl, info, &ops);
}

void cma27::Factorize(double** A)
{
    la = 1.5*info[4];
    factor = new double[la];
    
    // pass data
    int counter = 0;
    for (int i=0; i<nz; i++)
    {
        for (int j=i; j<n; j++)
        {
            if (fabs(A[i][j]) > 1e-5)
            {
                factor[counter] = A[i][j];
                counter++;
            }
        }
    }
    
    ma27bd_(&n, &nz, irn, icn, factor, &la, iw, &liw,
            ikeep,  &nsteps, &maxfrt, iw1,
            icntl,  cntl, info);
}

void cma27::Solve(double* rhs)
{
    double* w = new double[maxfrt]; // double workspace
    sol = new double[n];
    for (int i=0; i<n; i++)
    {
        sol[i] = rhs[i];
    }
    ma27cd_(&n, factor, &la, iw, &liw, w, &maxfrt, sol, iw1,
            &nsteps, icntl, info);
    delete[] w;
}

double* cma27::getSol()
{
    return sol;
}
#endif