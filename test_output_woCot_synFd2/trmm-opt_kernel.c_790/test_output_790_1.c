#pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'N'
// => Form B := alpha*A**T*B,
//A is TRANSA = 'T'
// => A is N-by-N
//B is TRANSB = 'N'
// => B is N-by-M
// => => product is N-by-M
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{60}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{5}
    for (j = 0; j < 60; j++) {
      A[i][j] *= alpha;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{2}
      for (k = 0; k < 60; k++) {
        B[i][j] += A[k][i] * B[k][j];
      }
    }
  }
  
#pragma endscop
}