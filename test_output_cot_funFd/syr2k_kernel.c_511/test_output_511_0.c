#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[4096],double A[4096],double B[4096])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
    for (j = i; j < 64; j++) {
      C[i * 64 + j] *= beta;
      k_col = i * 64;
      for (k = 0; k < 64; k++) {
        mult = alpha * A[k_col + k] * B[j * 64 + k];
        C[i * 64 + j] += mult;
      }
    }
  }
}