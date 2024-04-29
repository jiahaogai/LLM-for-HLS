#pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'N'
// => Form B := alpha*A**T*B,
//A is TRANSA = 'T'
// => A is NIxNK
//B is NIxNJ
// => B is modified
//TRANSAB = 'N'
// => Form B := alpha*A*B
//A is TRANSA = 'T'
// => A is NKxNI
//B is NKxNJ
// => B is modified
  for (i = 0; i < 60; i++) {
     for (j = 0; j < 80; j++) {
       B[i][j] *= alpha;
     }
     
#pragma ACCEL PIPELINE auto{off}
     
#pragma ACCEL TILE FACTOR=auto{1}
     
#pragma ACCEL PARALLEL FACTOR=auto{1}
     for (k = 0; k < 60; k++) {
       for (j = 0; j < 80; j++) {
         B[i][j] += A[k][i] * B[k][j];
       }
     }
    
#pragma ACCEL PIPELINE auto{off}
     
#pragma ACCEL TILE FACTOR=auto{80}
     
#pragma ACCEL PARALLEL FACTOR=auto{1}
     for (j = 0; j < 80; j++) {
       B[i][j] *= alpha;
     }
     
#pragma ACCEL PIPELINE auto{off}
     
#pragma ACCEL TILE FACTOR=auto{1}
     
#pragma ACCEL PARALLEL FACTOR=auto{1}
     for (k = 0; k < 60; k++) {
       for (j = 0; j < 80; j++) {
         B[k][j] += A[k][i] * B[i][j];
       }
     }
     
#pragma ACCEL PIPELINE auto{}
     
#pragma ACCEL TILE FACTOR=auto{1}
     
#pragma ACCEL PARALLEL FACTOR=auto{2}
     for (j = 0; j < 80; j++) {
       B[i][j] *= alpha;
     }
     
#pragma ACCEL PIPELINE auto{}
     
#pragma ACCEL TILE FACTOR=auto{1}
     
#pragma ACCEL PARALLEL FACTOR=auto{1}
     for (k = 0; k < 60; k++) {
       for (j = 0; j < 80; j++) {
         B[k][j] += A[k][i] * B[i][j];
       }
     }
     
#pragma ACCEL PIPELINE auto{off}
     
#pragma ACCEL TILE FACTOR=auto{8}
     
#pragma ACCEL PARALLEL FACTOR=auto{1}
     for (j = 0; j < 80; j++) {
       B[i][j] *= alpha;
     }
     
#pragma ACCEL PIPELINE auto{}
     
#pragma ACCEL TILE FACTOR=auto{1}
     
#pragma ACCEL PARALLEL FACTOR=auto{1}
     for (k = 0; k < 60; k++) {
       for (j = 0; j < 80; j++) {
         B[k][j] += A[k][i] * B[i][j];
       }
     }
     
#pragma ACCEL PIPELINE auto{off}
     
#pragma ACCEL TILE FACTOR=auto{1}
     
#pragma ACCEL PARALLEL