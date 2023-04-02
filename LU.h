//LU.h

// --------------------------
// Forward Phase
// --------------------------

int Lcol = -1;

for (int pivotRow = 0 ; pivotRow < m ; ++pivotRow) 
  {
    pivotCol = findPivot(m,n, A, b, pivotRow,pivotRow);
    
    // Populate L during elimination
    

    ++Lcol;
   // L[pivotRow][pivotRow] = 1.0; // diagonal elements of L are 1
    
    double fac = A[pivotRow][pivotCol];
    for(int i = pivotRow; i < m; ++i){
      L[i][Lcol] = A[i][pivotCol] / fac;

    }
    
    //  .......
    
    // Now, eliminate
    
    for ( int elimRow = pivotRow + 1 ; elimRow < m ; ++ elimRow )
      {
	  fac = -A[elimRow][pivotCol]/A[pivotRow][pivotCol];

    //L[elimRow][pivotCol] = -fac; // store multipliers in L
    
    for ( int col = pivotCol ; col < n ; ++col ) A[elimRow][col] += A[pivotRow][col] * fac;
    
    b[elimRow] += b[pivotRow] * fac;
        }
    }

// --------------------------
// Print Echelon Form
// --------------------------

printSystem("** Echelon Form **" , m , n , A  , b );
printSystem("** L **  "          , m , m , L  , b );

// --------------------------
// Check LU
// --------------------------

MatMat( L , m , A , n , m , LU );
printSystem("** LU Check **  "  , m , n , LU  , b );
