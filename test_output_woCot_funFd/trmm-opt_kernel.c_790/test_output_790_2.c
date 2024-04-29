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
//A is NIxNK
//B is NKxNJ
// => Product defined as:
//for(k=0;k<60;k++) {
//for(j=0;j<80;j++) {
//B[k][j] *= alpha;
//for(i=0;i<60;i++) {
//B[k][j] += A[i][k] * B[i][j];
//}
//}
//}
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{60}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (k = 0; k < 60; k++) {
    
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{10}
    for (j = 0; j < 80; j++) {
      B[k][j] *= alpha;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (i = 0; i < 60; i++) {
        B[k][j] += A[i][k] * B[i][j];
      }
    }
  }
  
#pragma endscop
}