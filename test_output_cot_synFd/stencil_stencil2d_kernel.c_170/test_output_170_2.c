Code: #pragma ACCEL kernel

void kernel_1(double A[256],double tmp[64],double B[64])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 0; j < 64; j++) {
    tmp[j] = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{16}
    loopi:
    for (i = 0; i < 256; i++) {
      tmp[j] += A[i] * B[i & 63];
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before ‘-’ token
    2 | - 
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:17:36: warning: multi-character character constant [-Wmultichar]
   17 |   int i;
      |                    ^~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:18:36: warning: multi-character character constant [-Wmultichar]
   18 |   int j;
      |                    ^~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:20:3: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘{’ token
   20 |   {
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:22:5: error: expected ‘{’ at end of input
   22 | 
      |     ^

Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_2(double A[256],double B[64])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 0; j < 64; j++) {
    B[j] = 0.0;
    
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{1}
    loopi:
    for (i = 0; i < 256; i++) {
      B[j] += A[i] * cos(0.112 * ((double )i * (double )j));
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before ‘-’ token
    2 | - 
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:17:36: warning: multi-character character constant [-Wmultichar]
   17 |   int i;
      |                    ^~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:18:36: warning: multi-character character constant [-Wmultichar]
   18 |   int j;
      |                    ^~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:20:3: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘{’ token
   20 |   {
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:22:5: error: expected ‘{’ at end of input
   2