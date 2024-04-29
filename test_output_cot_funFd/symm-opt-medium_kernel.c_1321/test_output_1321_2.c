#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[200][240],double A[200][200],double B[200][240])
{
  int m;
  int n;
  int k;
  int l;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (m = 0; m < 200; m++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (n = 0; n < 240; n++) {
      C[m][n] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 200; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
      for (l = 0; l < 240; l++) {
        C[m][l] += alpha * A[m][k] * B[k][l];
      }
    }
  }
}