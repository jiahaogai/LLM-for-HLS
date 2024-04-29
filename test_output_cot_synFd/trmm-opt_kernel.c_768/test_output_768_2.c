#pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
void kernel_gemm(double A[60][60],double B[60][80],double C[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 80; j++) {
      double sum = (double )0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      inner:
      for (k = 0; k < 60; k++) {
        k_col = k * 80;
        mult = A[i][k] * B[k][j];
        sum += mult;
      }
      C[i][j] = sum;
    }
  }
}
#pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
void kernel_gemm_1(double A[60][60],double B[60][80],double C[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 80; j++) {
      double sum = (double )0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner:
      for (k = 0; k < 60; k++) {
        k_col = k * 80;
        mult = A[i][k] * B[k][j];
        sum += mult;
      }
      C[i][j] = sum;
    }
  }
}