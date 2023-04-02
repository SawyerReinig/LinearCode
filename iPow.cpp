#include "iPow.h"

#include "LUsolve.h"


// =========================================================================
// M A I N   P R O G R A M
// =========================================================================

int main(int argc, char *argv[])
{
  int m; // number of rows
  int n; // number of columns

  #include "setCase.h"

  // ---------------------------------------------
  // Set up Inverse Power Method
  // ---------------------------------------------

  int    iter      = 0; //The current iteration of the Inverse Power Method. //The maximum number of iterations allowed for the Inverse Power Method.
  int    maxIter   = 100;  //The maximum number of iterations allowed for the Inverse Power Method.
  int    converged = 0;    //A flag indicating whether or not the Inverse Power Method has converged.
  double tol       = 0.00000001;   //The tolerance used to determine convergence of the Inverse Power Method.
  double mu;            //The estimate of the eigenvalue of the matrix A.
  double mu_old    = mu;//The previous estimate of the eigenvalue of the matrix A.
  double lambda;        //The final estimate of the eigenvalue of the original matrix A.

  double x[n];     // Used during Inverse Power Method Iteration, see class notes
  double xhat[n];  //   "   "       "       "      "      "        "    "     "  A vector used during Inverse Power Method Iteration.

  // Compute initial guess at x
  
   for (int i = 0; i < n; i++) x[i] = 1.0;  //this is setting the x vector, IDK? Make sure to fill this in

 // Save new A = (A - alpha*I) in Asave:

 for (int i = 0; i < n; i++){
  A[i][i] = A[i][i] - alpha;     // A is now (A - alpha I)
 }

  iLOOP jLOOP Asave[i][j] = A[i][j]; 
  


  // Print (A - alpha*I)
  
  printSystem("A-alphaI", m, n, Asave, b );     //string message, int m, int n, double **A, double *b
  
  // ---------------------------------------------
  // Perform LU factorization of new A
  // ---------------------------------------------

  #include "LU.h"

  // A now stores what.?  Point to the upper triangular A with  U:

    double **U = A;

  // ---------------------------------------------
  // Inverse Power Method Iterations
  // ---------------------------------------------

  while (  converged != 1 )
    {

      // Max iteration check
      
      if (iter >= maxIter) {  cout << "Max iterations exceeded." << endl;  exit(0); }

      // Step 2a: Compute xhat (Solve  (A - alpha I) * xhat = x)

      LUsolve(L , U , xhat , x , m , n , Asave );   // Asave is passed to check solution
      
      // Step 2b: Scale xhat so that the largest value = 1
      mu = 0.0; 

      for (int i = 0; i < m; i++) {

        if (fabs(xhat[i]) > fabs(mu)) {

          mu = xhat[i];

        }
        
      }
      for (int i = 0; i < n; i++) {
        xhat[i] /= mu;
        x[i] = xhat[i]; 
      }

      // Step 2c: Check for convergence and update mu_old

        if (fabs(mu - mu_old) < tol) {
          converged = 1;
        }
      mu_old = mu;

      // // Step 2d: Update x and mu
      // double sum = 0.0;
      // for (int i = 0; i < n; i++) {
      //   sum += xhat[i] * x[i];
      // }
      // mu = 1.0 / sum;
      // for (int i = 0; i < n; i++) {
      //   x[i] = xhat[i];
      // }

      iter++; 
      cout << "iter = " << iter << " mu = " << mu << endl;
      
    }

  // Compute final estimate for eigenvalue of original A, Aoriginal:

    lambda = alpha + 1/mu;
  
    cout << caseName << ": Inverse Power Method Converged in " << iter << " iterations." << endl;
    cout << caseName << ": =========================== Results " << endl;
    cout << caseName << ": mu = " << mu << endl;
    cout << caseName << ": lambda = " << lambda << endl;
    cout << caseName << ": ===========================         " << endl;
  
  
  // ---------------------------------------------
  // Test Eigenvalue/Eigenvector
  // ---------------------------------------------

    // Print eigenvector and Aoriginal * eigenvector, computing the ratio
    // to see how consistent that ratio is.

    double Ax[m];

    iLOOP Ax[i] = 0.0; 

    iLOOP jLOOP Ax[i] += xhat[j] * Aoriginal[i][j];  

    // for(int i = 0; i < n; i++){
    //   cout << "x of " << i << "= " << x[i] <<endl; ;  
    // }
    
      iLOOP printf("%s: E-vector Check:     x[%d] = %5.2f     Ax[%d] = %5.2f     ratio = %5.2f\n",
      caseName.c_str(), i, xhat[i], i, Ax[i], x[i]/Ax[i]);

      
    
  
}

