Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{128}
    for (j = 0; j < 64 + 2; j++) {
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[((i - 1) * 64 + j - 1) * 9 + k];
      }
      sol[i * (64 + 2) + j] = sum;
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before ‘-’ token
    2 | #pragma ACCEL kernel
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:21:1: error: expected identifier or ‘(’ before ‘-’ token
   21 | #pragma ACCEL PIPELINE auto{off}
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:22:1: error: expected identifier or ‘(’ before ‘-’ token
   22 | #pragma ACCEL TILE FACTOR=auto{1}
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:23:1: error: expected identifier or ‘(’ before ‘-’ token
   23 | #pragma ACCEL PARALLEL FACTOR=auto{1}
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:31:1: error: expected identifier or ‘(’ before ‘i’
   31 |   for (i = 0; i < 128 + 2; i++) {
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:35:1: error: expected identifier or ‘(’ before ‘j’
   35 |   for (j = 0; j < 64 + 2; j++) {
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:40:1: error: expected identifier or ‘(’ before ‘k’
   40 |   for (k = 0; k < 9; k++) {
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:46:1: error: expected identifier or ‘(’ before ‘sum’
   46 |     double sum = 0.0;
      |     ^~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:50:1: error: expected identifier or ‘(’ before ‘k’
   50 |     for (k = 0; k < 9; k++) {
      |     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:56:1: error: expected identifier or ‘(’ before ‘i’
   56 |   for (i = 0; i < 128 + 2; i++) {
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:60:1: