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
    for (j = 0; j <= i; j++) {
      double sum = 0.0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{240}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 64; k++) {
        k_col = k * 64;
        mult = alpha * A[i * 64 + k];
        sum += mult * C[k_col + j];
      }
      C[i * 64 + j] = sum + beta * C[i * 64 + j];
    }
  }
}