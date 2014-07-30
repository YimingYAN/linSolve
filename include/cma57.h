/*
 * Header file for cma57
 * Created by Yiming Yan
 * 29 July 2014
 */
#ifndef maSolver_cma57_h
#define maSolver_cma57_h

#include <cmath>

class cma57
{
public:
    cma57(const int n, const int nz, double** A);
    
    void Initialize();
    void Analyze();
    void Factorize();
    void Solve(double* rhs);
    
    double* getSol();
    
protected:
    int n;              // order of matrix, namely number of rows or cols
    int nz;             // number of nonzeros entries
    
    double cntl[5];     // double array of length 5; contains double control values
    int icntl[20];      // integer array of length 20; contaitns integer control values
    
    int* irn;           // row index of input
    int* jcn;           // col index of input
    
    int lkeep;          // length of keep; lkeep ≥  5*n+nz+MAX(n,nz)+42
    int* keep;          // integer workspace of length lkeep
    int* iw;            // integer array of 5*n; pivot sequence
    int info[40];       // integer array of length 40
    double rinfo[20];   // double array of length 20
    
    double* a;          // double array of data
    double* fact;       // double array of length lfact; holds the entries of the factors
    int lfact;          // length of fact
    int* ifact;         // integer array; integer indexing info on the matrix factors
    int lifact;         // length of ifact
    
    int job;            // integer; job = 1 if solving system AX=B
    
    double* sol;        // Solution
    
    
    
};

#ifdef __cplusplus
extern "C" {
#endif
    extern void ma57id_(double cntl[5], int icntl[20]);
    extern void ma57ad_(int *n, int *nz, int *irn, int *jcn,
                        int *lkeep, int *keep, int *iw,
                        int icntl[20], int info[40], double rinfo[20]);
    extern void ma57bd_(int *n, int *nz, double *a, double *fact,
                        int *lfact, int *ifact, int *lifact, int *lkeep,
                        int *keep, int *iw, int icntl[20], double cntl[5],
                        int info[40], double rinfo[20]);
    extern void ma57cd_(int *job, int *n, double *fact, int *lfact,
                        int *ifact, int *lifact, int *nrhs, double *rhs,
                        int *lrhs, double *w, int *lw, int *iw,
                        int icntl[20], int info[40]);
    /*
     * w        - double array of length lw; workspace
     * lw       - integer, length of w
     * iw       - integer array of length n; workspace
     */
#ifdef __cplusplus
}
#endif

cma57::cma57(const int i_n, const int i_nz, double** A)
{
    n = i_n;
    nz = i_nz;
    
    irn = new int[nz];
    jcn = new int[nz];
    
    a = new double[nz];
    
    int counter = 0;
    for (int i=0; i<nz; i++)
    {
        for (int j=i; j<n; j++)
        {
            if (fabs(A[i][j]) > 1e-5)
            {
                irn[counter] = i+1; // fortran index
                jcn[counter] = j+1; // start from 1
                a[counter] = A[i][j];
                
                counter++;
            }
        }
    }
    
    lkeep = (nz > n) ? (5*n+2*nz+42) : (6*n+nz+42);
    keep = new int[lkeep];
    iw = new int[5*n];
    
    job = 1;
}

void cma57::Initialize()
{
    ma57id_(cntl, icntl);
    //icntl[4] = 4;
}

void cma57::Analyze()
{
    ma57ad_(&n, &nz, irn, jcn, &lkeep, keep, iw,
            icntl, info, rinfo);
}

void cma57::Factorize()
{
    lfact = 1.2*info[8];
    fact = new double[lfact];
    lifact = 1.2*info[9];
    ifact = new int[lifact];
    
    ma57bd_(&n, &nz, a, fact, &lfact, ifact, &lifact, &lkeep,
            keep, iw, icntl, cntl, info, rinfo);
}

void cma57::Solve(double* rhs)
{
    int nrhs = 1;               // number of right hand side being solved
    int lw = 1.2*n*nrhs;        // length of w; lw>=n*nrhs
    double* w = new double[lw]; // double workspace
    int lrhs = n;               // integer, lenght of rhs
    
    sol = new double[n];
    for (int i=0; i<n; i++)
    {
        sol[i] = rhs[i];
    }
    
    ma57cd_(&job, &n, fact, &lfact, ifact, &lifact, &nrhs, sol,
            &lrhs, w, &lw, iw, icntl, info);
    delete[] w;
}

double* cma57::getSol()
{
    return sol;
}
#endif
