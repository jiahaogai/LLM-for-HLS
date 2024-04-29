#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[250][250],double A[250][250],double B[250][250])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B**T + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 250; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{3}
    for (j = 0; j < 250; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (k = 0; k < 250; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{70}
      for (j = 0; j < 250; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
}