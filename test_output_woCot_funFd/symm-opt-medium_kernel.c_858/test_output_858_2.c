The HLS code snippet is shown below:
 #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[200][240],double A[200][200],double B[200][240])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{30}
    for (j = 0; j < 240; j++) {
      double tmp = B[i][j];
      
#pragma ACCEL PARALLEL reduction = C FACTOR=auto{32}
      for (k = 0; k < 200; k++) {
        if (k < i) {
          C[k][j] += alpha * tmp * A[i][k];
        }
      }
      double temp2 = (double )0;
      
#pragma ACCEL PARALLEL reduction = temp2 FACTOR=auto{64}
      for (k = 0; k < 200; k++) {
        if (k < i) {
          temp2 += B[k][j] * A[i][k];
        }
      }
      C[i][j] = beta * C[i][j] + alpha * tmp * A[i][i] + alpha * temp2;
    }
  }
//#pragma endscop
}