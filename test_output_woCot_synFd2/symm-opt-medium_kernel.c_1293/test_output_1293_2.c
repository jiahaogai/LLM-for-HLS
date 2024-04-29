#pragma ACCEL kernel

void kernel_symm(int M,int N,double alpha,double beta,double C[256][256],double A[256][256],double B[256][256])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 256; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 256; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{4}
      for (k_col = 0; k_col < 256; k_col++) {
        mult = alpha * A[i][k] * B[k][k_col];
        C[i][k_col] += mult;
      }
    }
  }
}