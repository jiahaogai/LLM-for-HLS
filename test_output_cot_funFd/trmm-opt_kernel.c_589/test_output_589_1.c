Code: 
 #pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'N'
// => Form B := alpha*A'*B,
  for (i = 0; i < 60; i++) {
     for (j = 0; j < 80; j++) {
       B[i][j] *= alpha;
     }
     
#pragma ACCEL PIPELINE auto{}
     
#pragma ACCEL TILE FACTOR=auto{1}
     
#pragma ACCEL PARALLEL FACTOR=auto{15}
     for (k = 0; k < 60; k++) {
        for (j = 0; j < 80; j++) {
          B[i][j] += A[k][i] * B[k][j];
        }
      }
     }
}