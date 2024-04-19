#pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,double C[200][220],double A[200][240],double B[240][220],double tmp[200][220])
{
  int i;
  int j;
  int k;
//#pragma scop
/* D := alpha*A*B*C + beta*D */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 220; j++) {
      tmp[i][j] = 0.0;
      
#pragma ACCEL PARALLEL reduction = tmp FACTOR=auto{8}
      for (k = 0; k < 240; ++k) {
        tmp[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 220; j++) {
      C[i][j] *= beta;
      
#pragma ACCEL PARALLEL reduction = C FACTOR=auto{1}
      for (k = 0; k < 240; ++k) {
        C[i][j] += tmp[i][k] * C[k][j];
      }
    }
  }
//#pragma endscop
}