/*
 * Header file for cma57
 * Created by Yiming Yan
 * 29 July 2014
 */
#ifdef __cplusplus
extern "C" {
#endif
    extern void ma57id_(double cntl[5], int icntl[20]);
    extern void ma57ad_(int *n, int *ne, int *irn, int *jcn,
                        int *lkeep, int *keep, int *iwork,
                        int icntl[20], int info[40], double rinfo[20]);
    /*
     * n        - dimension of matrix A
     * ne       - length of irn and jcn
     * irn      - row index of input
     * jcn      - col index of input
     * lkeep    - length of array keep; 
     *            lkeep ≥ 5*N+NE+MAX(N,NE)+42
     * keep     - integer array; pivot sequence
     * iwork    - integer array of length 5*N; workspace
     * info     - integer array of length 40
     * rinfo    - double array of length 20
     */
    //extern void ma57bd_();
    //extern void ma57cd_();
    //extern void ma57dd_();
    //extern void ma57ed_();
#ifdef __cplusplus
}
#endif
