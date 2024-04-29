Code: #pragma ACCEL kernel

void kernel_jacobi_128_64(double *in,double *out)
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 64; j++) {
      double sum = 0.0;
      
#pragma ACCEL PARAM=in FACTOR=auto{16}
      for (k = 0; k < 16; k++) {
        sum += in[(i * 16 + k) * 64 + j];
      }
      out[i * 64 + j] = 0.5 * (sum + in[i * 64 + j]);
    }
  }//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before ‘-’ token
    2 | - Pass the 'in' array to the hardware accelerator.
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:12: warning: multi-character character constant [-Wmultichar]
    2 | - Pass the 'in' array to the hardware accelerator.
      |            ^~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:12: warning: multi-character character constant [-Wmultichar]
    5 | - Pass the 'out' array to the hardware accelerator.
      |            ^~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:8:18: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘<’ token
    8 |    for (i = 0; i < 128; i++) {
      |                  ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:8:26: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘++’ token
    8 |    for (i = 0; i < 128; i++) {
      |                          ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:19:1: error: expected identifier or ‘(’ before ‘}’ token
   19 | }
      | ^

Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_jacobi_128_64_offload(double *in,double *out)
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 64; j++) {
      double sum = 0.0;
      
#pragma ACCEL PARAM=in FACTOR=auto{16}
      for (k = 0; k < 16; k++) {
        sum += in[(i * 16 + k) *