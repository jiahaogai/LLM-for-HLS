Code: #pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double sum;
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}
    for (j = 0; j < 60; j++) {
      A[i][j] *= alpha;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 80; k++) {
      
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{30}
      for (j = 0; j < 60; j++) {
        B[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  
#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:16:3: error: expected identifier or ‘(’ before ‘for’
   16 |   for (i = 0; i < 60; i++) {
      |   ^~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:16:17: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘<’ token
   16 |   for (i = 0; i < 60; i++) {
      |                 ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:16:24: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘++’ token
   16 |   for (i = 0; i < 60; i++) {
      |                        ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:37:1: error: expected identifier or ‘(’ before ‘}’ token
   37 | }
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_trmm’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:46:7: error: ‘C’ undeclared (first use in this function)
   46 |       C[i][j] = sum;
      |       ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:46:7: note: each undeclared identifier is reported only once for each function it appears in

Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double sum;
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}
    for (j = 0; j < 60; j++) {
      A[i][j] *= alpha;
    }
    
#pragma ACCEL PIPELINE auto{flatten