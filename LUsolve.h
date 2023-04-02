// LUsolve.h
// ---------------------------------------------
// Solve (A - labmda I) xhat = x
// ---------------------------------------------

// A = LU, so solve the above system in a 2-step process

void LUsolve(double **L,
             double **U,
             double *Sol,
             double *RHS, int m, int n, double **A)
{
  double y[n];

  // Solve L*y = x

  for(int i = 0; i < m; i++){
    y[i] = RHS[i]; 
  }

  for(int Row = 0; Row < n; Row++){
    for(int Col = Row + 1; Col < m; Col++){

      double factor = L[Col][Row]; 
      y[Col] -= y[Row] * factor; 

    }
  }

  // Solve U*Sol = RHS

 for(int i = 0; i < m; i++){
  Sol[i] = y[i]; 
 }

for(int i = n - 1; i >= 0; i--){
  
  int row = i; 
  double factor = U[row][i];
  Sol[i] = Sol[i] / factor; 
    for(int j = row - 1; j >= 0; j--){

      factor = U[j][i]; 
      Sol[j] -= Sol[row] * factor; 

    }
  }



  // Check solution LU * Sol = RHS, or Asave*Sol = RHS

  if (n == m) // Must be true for there to be a unique solution

    for (int i = 0; i < m; ++i)
    {
      double error = RHS[i];
      for (int j = 0; j < n; ++j)
        error -= A[i][j] * Sol[j];

      if (fabs(error) > 1.e-10)
      {
        cout << "LU Solve failed\n";
        exit(0);
      }
    }
}
