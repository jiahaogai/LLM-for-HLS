#pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form B := alpha*A*B,
  for (i = 0; i < 60; i++) {
     for (j = 0; j < 80; j++) {
       B[i][j] *= alpha;
     }
  }
//TRANSA = 'N'
//TRANSB = 'N'
// => Form B := alpha*A*B,
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (k = 0; k < 60; k++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      A[k][j] *= B[k][j];
    }
  }
}