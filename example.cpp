#include "MA27.h"
#include "MA57.h"
#include "linSolve.h"
#include <iostream>

using namespace std;

void printSol(int n, const double* sol);
void printSystem(int m, int n, double** A, double* b);

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
    b[0] = 8.; b[1] = 45.; b[2] = 31.; b[3] = 15.; b[4] = 17.;
    double b2[n];
    b2[0] = 1.; b2[1] = 2.; b2[2] = 1.; b2[3] = 2.; b2[4] = 3.;

    double* sol27_1;
    double* sol27_2;
    double* sol57_1;
    double* sol57_2;
    /* ====== End Data ====== */
    
    /* ====== Test linSolve ====== */
    cout<<"====== Test linSolve ======"<<endl;
	linSolve<double*, double**,MA27> linSolveT27(n, nz, A);
    linSolve<double*, double**,MA57> linSolveT57(n, nz, A);
    /*
     * Here we set the vector type to be double* and the matrix type to be double**
     * Currently it only accepts dynamically allocated arrays, 
     * becasue of the implementation of MA27 and MA57.
     */
    
    printSystem(n,n,A,b);
    
    /*
     * Test MA27
     */
    
    linSolveT27.Factorize();
    linSolveT27.Solve(b);
    sol27_1 = linSolveT27.getSol();
    
    cout<<"Solution for Ax = b using MA27:"<<endl;
    printSol(n, sol27_1);
    
    /*
     * Test MA57
     */
    linSolveT57.Factorize();
    linSolveT57.Solve(b);
    sol57_1 = linSolveT57.getSol();
    
    cout<<"Solution for Ax = b using MA57:"<<endl;
    printSol(n, sol57_1);
    
    /*
     * Just the change right hand side; no need to factorize the matirx again.
     */
    printSystem(n,n,A,b2);
    
    linSolveT27.Solve(b2);
    sol27_2 = linSolveT27.getSol();
    cout<<"Solution for Ax = b2 using MA27:"<<endl;
    printSol(n, sol27_2);
    
    linSolveT57.Solve(b2);
    sol57_2 = linSolveT57.getSol();
    cout<<"Solution for Ax = b2 using MA57:"<<endl;
    printSol(n, sol57_2);
    
    /* ====== End linSolve ====== */
    
    
    /* Release memory*/
    for (int i=0; i<5; i++)
    {
        delete[] A[i];
    }
    delete[] A;
    
    return 0;
}

void printSol(int n, const double* sol)
{
    cout<<"( "<<sol[0];
    for (int i=1; i<n; i++)
    {
        cout<<", "<<sol[i];
    }
    cout<<" )"<<endl;
}

void printSystem(int m, int n, double** A, double* b)
{
	int mid = (int) m/2;

	cout<<"\n\nThe linear system to solve: "<<endl;
	for (int i = 0; i < m; i++)
	{
		cout<<"[ ";
		for (int j=0; j<n; j++)
		{	if (fabs(A[i][j]) < 1e-05)
				cout<<"  ";
			else
				cout<<A[i][j]<<" ";
		}
		cout<<"]";
		cout<<"[ x_"<<to_string(i) <<"]";
		if (i == mid) cout<<" = ";
		else cout<<"   "; 
		cout<<"[ "<<b[i]<<" ]"<<endl;
	} 
    cout<<endl;


}
