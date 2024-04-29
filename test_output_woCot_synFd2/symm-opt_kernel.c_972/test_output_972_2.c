Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{80}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{15}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{15}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{__PARA__L1}
      for (j = 0; j < 80; j++) {
        k_col = k * 80;
        mult = alpha * A[i][k] * B[k][j];
        C[i][j_col + j] += mult;
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_symm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:32:7: error: duplicate label ‘splice’
   32 |       splice:
      |       ^~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:19:3: note: previous definition of ‘splice’ was here
   19 |   splice:
      |   ^~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:46:3: error: duplicate label ‘splice’
   46 |   splice:
      |   ^~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:19:3: note: previous definition of ‘splice’ was here
   19 |   splice:
      |   ^~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:54:5: error: duplicate label ‘k_col’
   54 |     k_col:
      |     ^~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:27:5: note: previous definition of ‘k_col’ was here
   27 |     k_col:
      |     ^~~~~

Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{80}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{15}
    for (j = 0; j <