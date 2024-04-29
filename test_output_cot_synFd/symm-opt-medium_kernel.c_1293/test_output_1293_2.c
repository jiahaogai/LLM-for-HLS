#pragma ACCEL kernel

void kernel_symm(int M,int N,double alpha,double beta,double C[400][400],double A[400][400],double B[400][400],double tmp[400][400])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 400; j++) {
      tmp[i][j] = 0.0;
      
#pragma ACCEL PARALLEL reduction = tmp FACTOR=auto{4}
      for (k = 0; k < 400; ++k) {
        tmp[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 400; j++) {
      C[i][j] *= beta;
      C[i][j] += tmp[i][j];
    }
  }
//#pragma endscop
}