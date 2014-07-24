extern "C" {
    extern void ma27id_(int icntl[30], double cntl[5]);
    /* MA27ID_ C++ interface for fortran routine MA27ID (Initialize)
     * icntl    -
     * cntl     -
     */
    
    extern void ma27ad_(int *n, int *nz, int *irn, int *icn, int iw[],
                        int *liw, int *ikeep, int *iw1, int *nsteps,
                        int *iflag, int icntl[30], double cntl[5],
                        int info[20], double *ops );
    /* MA27AD_ C++ interface for fortran routine MA27AD (Analyze)
     * n        - order of matrix, namely number of rows or cols
     * nz       - number of nonzeros entries
     * irn      - row index of input
     * icn      - col index of input
     * iw       - integer workspace of length liw
     * liw      - length of iw; at least 2*NZ+3*N+1 
                  (or NZ+3*N+1 if the pivot order is specified in ikeep)
     * ikeep    - integer array of 3*n; pivot sequence
     * iwl      - integer workspace array of length n
     * nsteps   - integer, to be set by ma27
     * iflag    - integer; 0 if pivot order chosen automatically; 
                  1 if the pivot order set by ikeep
     * info     - integer array of length 20
     * ops      - double, operations count
     */
    
    extern void ma27bd_(int *n, int *nz, int *irn, int *icn,
                   double *a, int *la, int iw[], int *liw,
                   int *ikeep, int *nsteps, int *maxfrt, int *iw1,
                   int icntl[30], double cntl[5], int info[20]);
    /* MA27BD_ C++ interface for fortran routine MA27BD (Factorize)
     * a        - data array
     * la       - length of a
     * maxfrt   - integer, to be set by ma27
     */
    
    extern void ma27cd_(int *n, double *a, int *la, int iw[], int *liw,
                       double *w, int *maxfrt, double *rhs, int *iw1,
                       int *nsteps, int icntl[30], int info[20]);
    /* MA27CD_ C++ interface for fortran routine MA27CD (Solve)
     * w        - double workspace
     * rhs      - right hand side of the linear system (b in Ax=b);
     *            after the solving process, rhs contains the solution.
     */
}

