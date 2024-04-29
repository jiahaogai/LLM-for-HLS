#pragma ACCEL kernel

void kernel_syrk(int n,double alpha,double beta,double C[4096],double A[4096])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
    for (j = 0; j < 64; j++) {
      C[i * 64 + j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{240}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 64; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
      for (j = 0; j < 64; j++) {
        k_col = k * 64;
        mult = alpha * A[k_col + j];
        C[i * 64 + j] += mult;
      }
    }
  }
}