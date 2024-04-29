Code: #pragma ACCEL kernel

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
  int m = 60;
  int k1 = 60;
//B is TRANSB = 'N'
  int n = 80;
  int k2 = 60;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction = A FACTOR=auto{1}
    for (j = 0; j < 60; j++) {
      A[i][j] *= alpha;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{80}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction = sum FACTOR=auto{60}
      for (j = 0; j < 80; j++) {
        double sum = 0.0;
#pragma ACCEL PARALLEL reduction = y FACTOR=auto{80}
        for (k2 = 0; k2 < 60; k2++) {
          sum += A[k2][i] * B[k2][j];
        }
        A[k][i] = sum;
      }
    }
  }
}