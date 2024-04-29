#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[4096],double A[4096],double B[4096])
{
  int i;
  int j;
  int k;
  int j_col;
  int k_row;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = i; j < 64; j++) {
      j_col = j * 64;
      C[j_col + i] *= beta;
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
      for (k = 0; k < 64; k++) {
        k_row = k * 64;
        mult = alpha * A[k_row + i] * B[j_col + k];
        C[j_col + i] += mult;
      }
    }
  }
}