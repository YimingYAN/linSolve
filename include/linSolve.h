/*
 * Header file for linSolve
 * Created by Yiming Yan
 * 05 Aug. 2014
 */


#ifndef _linSolve_h
#define _linSolve_h

template <typename T_Vec, typename T_Mat, class aSolver>
class linSolve
{
public:
    linSolve(const int n, const int nz, T_Mat A)
    {
        theSolver = new aSolver(n, nz, A);
    }
    void Factorize() {      theSolver->Factorize();     }
    void Solve(T_Vec rhs) { theSolver->Solve(rhs);      }
    T_Vec getSol() {        return theSolver->getSol(); }
    
private:
    aSolver* theSolver;
};

#endif
