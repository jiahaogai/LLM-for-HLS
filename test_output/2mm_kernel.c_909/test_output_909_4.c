#pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,double C[40][80],double A[40][70],double B[70][50],double D[40][50])
{
  int i;
  int j;
  int k;
//#pragma scop
/* D := alpha*A*B*C + beta*D */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 80; j++) {
      double tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{70}
      for (k = 0; k < 50; ++k) {
        tmp += alpha * A[i][k] * B[k][j];
      }
      D[i][j] = beta * D[i][j] + tmp;
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 50; j++) {
      double tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{40}
      for (k = 0; k < 70; ++k) {
        tmp += A[i][k] * C[k][j];
      }
      tmp = alpha * tmp + beta * C[i][j];
      for (l = 0; l < 80; ++l) {
        D[i][l] += tmp * B[j][l];
      }
    }
  }
//#pragma endscop
}