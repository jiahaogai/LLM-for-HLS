Code: #pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'N'
// => Form B := alpha*A^T*B,
//A is TRANSA = 'T'
  int m = 60;
  int n = 60;
  int k = 60;
  int q = 80;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{80}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{60}
      for (k = 0; k < 60; k++) {
        sum += alpha * A[k][i] * B[k][j];
      }
      B[i][j] = sum;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_trmm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:15:7: error: redeclaration of ‘k’ with no linkage
   15 |   int k = 60;
      |       ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:7: note: previous declaration of ‘k’ was here
    7 |   int k;
      |       ^

Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'N'
// => Form B := alpha*A^T*B,
//A is TRANSA = 'T'
  int m = 60;
  int n = 60;
  int k = 60;
  int q = 80;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{80}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{60}
      for (k = 0; k < 60; k++) {
        sum += alpha * A[k][i] * B[k][j];
      }
      B[i][j] = sum;
    }
  }
}