#pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,double C[40][80],double A[40][60],double B[60][80],double tmp[40][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{60}
    for (j = 0; j < 80; j++) {
      tmp[i][j] = 0.0;
      for (k = 0; k < 60; ++k) {
        tmp[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{40}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
      for (k = 0; k < 60; ++k) {
        C[i][j] += alpha * tmp[i][k] * A[k][j];
      }
    }
  }
//#pragma endscop
}