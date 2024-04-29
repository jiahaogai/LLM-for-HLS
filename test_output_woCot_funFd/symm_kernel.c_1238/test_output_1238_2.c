Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double mult;
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{60}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{80}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{1}
      for (j = 0; j < 80; j++) {
        double temp1 = 0.0;
        mult = alpha * A[i][k];
        
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{2}
        for (long long n = 0; n < 80; n++) {
          temp1 += mult * B[k][n];
        }
        C[i][j] += temp1;
      }
    }
  }
  
#pragma endscop
}