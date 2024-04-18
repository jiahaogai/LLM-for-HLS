#include <math.h>
 #pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,double tmp[40][50],double A[40][70],double B[70][50],double C[50][80],double D[40][80])
  for(int i = 0;
      i < 40;
      i++) {
    for(int j = 0;
        j < 50;
        j++) {
      tmp[i][j] = 0.0;
      for(int k = 0;
          k < 70;
          k++) {
        tmp[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  for(int i = 0;
      i < 40;
      i++) {
    for(int j = 0;
        j < 80;
        j++) {
      D[i][j] *= beta;
      for(int k = 0;
          k < 50;
          k++) {
        D[i][j] += alpha * tmp[i][k] * C[k][j];
      }
    }
  }
}