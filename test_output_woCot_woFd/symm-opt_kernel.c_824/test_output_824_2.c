- `#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{__PARA__L1}`: Execute the loop with reduction on variable `temp1` and optimize parallelization based on L1 cache.

### Template:
 #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double temp1 = 0.0;
  double temp2 = 0.0;
  int k_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{60}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{20}
    middle:
    for (j = 0; j < 80; j++) {
      temp1 = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      inner:
      for (k = 0; k < 60; k++) {
        k_col = 60 * k + j;
        temp1 += A[i][k] * B[k][k_col];
      }
      temp2 = alpha * temp1 + beta * C[i][j];
      C[i][j] = temp2;
    }
  }
}