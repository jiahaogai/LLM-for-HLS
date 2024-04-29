- `C[i][j]`: Accesses the element `C[i][j]` of matrix `C`.
- `A[i][k]`: Accesses the element `A[i][k]` of matrix `A`.
- `B[k][j]`: Accesses the element `B[k][j]` of matrix `B`.
- `temp1 = 0.0`: Initializes the variable `temp1` to zero.
- `temp2 = 0.0`: Initializes the variable `temp2` to zero.
- `temp1 = A[i][k] * B[k][j]`: Performs the multiplication `A[i][k] * B[k][j]` and stores the result in `temp1`.
- `temp2 += temp1`: Accumulates the partial results in `temp2`.
- `C[i][j] = temp2 * alpha`: Multiplies the result `temp2` of the reduction operation with `alpha` and stores the result in `C[i][j]`.
- `C[i][j] = C[i][j] + beta * C[i][j]`: Adds the original value `C[i][j]` to the result of the reduction with coefficient `beta`.

#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double temp_x;
  double mul;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  spool:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    k_col:
    for (k_col = 0; k_col < 80; k_col += 8) {
      int k;
      
#pragma ACCEL PARALLEL reduction=temp_x FACTOR=auto{4}
      k = 0;
      while (k < 60) {
        double temp1 = 0.0;
        double temp2 = 0.0;
        int j;
        
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{2}
        j = 0;
        while (j < 8) {
          temp1 += A[i][k] * B[k][k_col + j];
          j++;
        }
        temp2 = temp1 * alpha;
        temp1 = C[i][k_col + 7] * beta;
        temp2 += temp1;
        C[i][k_col + 7] = temp2;
        k++;
      }
    }
  }
}