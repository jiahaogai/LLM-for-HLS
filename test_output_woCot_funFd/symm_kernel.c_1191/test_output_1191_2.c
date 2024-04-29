#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[4096],double A[4096],double B[4096])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{20}
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = i; j < 64; j++) {
      C[i * 64 + j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{80}
    for (k = 0; k < 64; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{16}
      for (j = k; j < 64; j++) {
        C[i * 64 + j] += alpha * A[i * 64 + k] * B[k * 64 + j];
      }
    }
  }
//#pragma endscop
}