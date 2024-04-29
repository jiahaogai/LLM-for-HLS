#pragma ACCEL kernel

void kernel_syrk(double alpha,double beta,double C[80][80],double A[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'T'
// => Form C := alpha*A*A**T + beta*C,
//A is NIxNK
//A**T is NKxNI
//C is NIxNJ
// => forall i in 0..79, j in 0..79, k in 0..59
//C[i][j] += alpha*A[i][k]*A[k][j]
//FIRST ACCESS
//A[i][k]
//SECOND ACCESS
//A[k][j]
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{16}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * A[k][j];
      }
    }
  }
  
#pragma endscop
}