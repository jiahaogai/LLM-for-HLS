#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{60}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
      for (j = 0; j < 80; j++) {
        double temp2 = 0.0;
        double temp1 = 0.0;
        int kidx;
        int jidx;
        int iidx;
        for (kidx = 0; kidx < 60; kidx++) {
          iidx = i + kidx;
          if (((iidx >= 0) && (iidx < 60))) {
            for (jidx = 0; jidx < 80; jidx++) {
              double L1_ij = A[iidx][kidx];
              double L2_ij = B[kidx][jidx];
              temp1 = L1_ij * L2_ij;
              if (((jidx >= 0) && (jidx < 80))) {
                temp2 += temp1;
              }
            }
          }
        }
        if (((j >= 0) && (j < 80))) {
          C[i][j] += temp2;
        }
      }
    }
  }
//#pragma endscop
}