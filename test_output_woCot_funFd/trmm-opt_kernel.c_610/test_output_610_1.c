#pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{8}

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'N'
// => Form B := alpha*A^T*B,
//A is TRANSA( = 'T') => A is n-by-n
//B is TRANSB( = 'N') => B is n-by-m
// => => product defined as follows:
//for(j = 0; j < m; j++) {
//for(i = 0; i < n; i++) {
//B[i][j] *= alpha * A[i][i];
//}
//}
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{80}
  for (j = 0; j < 80; j++) {
    
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{32}
    for (i = 0; i < 60; i++) {
      B[i][j] *= alpha * A[i][i];
    }
  }
}