#pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,double tmp[40][50],double A[40][70],double B[70][50],double C[50][80],double D[40][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{7}
    for (k = 0; k < 50; k++) {
      tmp[i][k] = 0.0;
      for (j = 0; j < 70; j++) {
        tmp[i][k] += A[i][j] * B[j][k];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction=D FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      D[i][j] *= beta;
      for (k = 0; k < 50; k++) {
        D[i][j] += alpha * tmp[i][k] * C[k][j];
      }
    }
  }
//#pragma endscop
}