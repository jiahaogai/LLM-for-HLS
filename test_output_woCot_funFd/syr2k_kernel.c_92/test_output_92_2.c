#pragma ACCEL kernel

void kernel_syr2k(int n,double alpha,double beta,double C[400][400],double A[400][300],double B[300][400])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B**T + beta*C,
//A is NXM (N=400, M=300)
//B is MXP (M=300, P=400)
//C is NXP (N=400, P=400)
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (k = 0; k < 300; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
      for (j = 0; j < 400; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
}