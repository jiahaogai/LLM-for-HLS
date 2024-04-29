#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[200][240],double A[200][200],double B[200][240])
{
  int m;
  int n;
  int p;
  int q;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (m = 0; m < 200; m++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (n = 0; n < 240; n++) {
      C[m][n] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 200; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
      for (p = 0; p < 240; p++) {
        C[m][p] += alpha * A[m][k] * B[k][p];
      }
    }
  }
//#pragma endscop
}