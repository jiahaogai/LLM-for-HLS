#pragma ACCEL kernel

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
    
#pragma ACCEL PARALLEL FACTOR=auto{80}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{32}
      for (j = 0; j < 80; j++) {
        double temp1 = 0.0;
        int index = k * 80 + j;
        double temp2 = 0.0;
        int index_2 = i * 80 + j;
        for (int r = 0; r < 60; ++r) {
          int index_3 = r * 80 + j;
          temp1 = A[r][k] * B[i * 60 + r][j];
          temp2 += temp1;
        }
        mult = alpha * temp2;
        C[i][j] += mult;
      }
    }
  }
  
#pragma endscop
}