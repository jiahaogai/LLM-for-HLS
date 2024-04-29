#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[200][240],double A[200][200],double B[200][240])
{
  int m;
  int n;
  int p;
  int q;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (m = 0; m < 200; m++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (n = 0; n < 240; n++) {
      C[m][n] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
    for (p = 0; p < 200; p++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (q = 0; q < 240; q++) {
        mult = alpha * A[p][m] * B[m][q];
        C[p][q] += mult;
      }
    }
  }
}