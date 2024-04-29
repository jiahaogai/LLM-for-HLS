#pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'N'
// => Form B := alpha*A*B,
//A is TRANSA( A ) = A(60,60)
//B is TRANSB( B ) = B(60,80)
// => FORM B := alpha*A(60,60)*B(60,80) = A(60,60)*B(80,60)
// => A(60,60) is TRANSA( A(60,60) )
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{60}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      B[i][j] *= alpha;
      
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{16}
      for (k = 0; k < 60; ++k) {
        B[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  
#pragma endscop
}