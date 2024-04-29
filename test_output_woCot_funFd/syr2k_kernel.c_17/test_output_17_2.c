#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[4096],double A[4096],double B[4096])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{80}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 64; j++) {
      C[i * 64 + j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 64; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
      for (j = 0; j < 64; j++) {
        C[i * 64 + j] += alpha * A[i * 64 + k] * B[k * 64 + j];
      }
    }
  }
}