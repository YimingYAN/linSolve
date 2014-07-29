/*
 * Header file for cma57
 * Created by Yiming Yan
 * 29 July 2014
 */
#ifdef __cplusplus
extern "C" {
#endif
    extern void ma57id_(double cntl[5], int icntl[20]);
    /*
     * cntl     - array of double; contains double control values
     * icntl    - array of  integer; contaitns integer control values
     */
    
    extern void ma57ad_(int *n, int *ne, int *irn, int *jcn,
                        int *lkeep, int *keep, int *iw,
                        int icntl[20], int info[40], double rinfo[20]);
    /*
     * n        - dimension of matrix A
     * ne       - length of irn and jcn
     * irn      - row index of input
     * jcn      - col index of input
     * lkeep    - length of array keep; 
     *            lkeep ≥ 5*n+ne+MAX(n,ne)+42
     * keep     - integer array; pivot sequence
     * iw       - integer array of length 5*N; workspace
     * info     - integer array of length 40
     * rinfo    - double array of length 20
     */
    
    extern void ma57bd_(int *n, int *ne, double *A, double *fact,
                        int *lfact, int *ifact, int *lifact, int *lkeep,
                        int *keep, int *iw, int icntl[20], double cntl[5],
                        int info[40], double rinfo[20]);
    /*
     * A        - double array of data
     * fact     - double array of length lfact; 
     *            holds the entries of the factors of the matrix A
     * lfact    - length of fact
     * ifact    - integer array;
                  holds integer indexing information on the matrix factors
     * lifact   - length of ifact
     */
    
    extern void ma57cd_(int *job, int *n, double *fact, int *lfact,
                        int *ifact, int *lifact, int *nrhs, double *rhs,
                        int *lrhs, double *w, int *lw, int *iw,
                        int icntl[20], int info[40]);
    /*
     * job      - integer; determines the system being solved 
     *            job = 1 if solving system AX=B
     * w        - double array of length; workspace
     * lw       - length of w; lw>=n*nrhs
     * nrhs     - number of right hand side being solved
     * rhs      - array of double; right hand side of the system
     * lrhs     - integer, lenght of rhs
     * w        - double array of length lw; workspace
     * lw       - integer, length of w
     * iw       - integer array of length n; workspace
     */
#ifdef __cplusplus
}
#endif
