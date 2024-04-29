Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp = 0;
  int elem;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      tmp = 0;
      k = 0;
      while (k < 9) {
        tmp += orig[i + (-4 + k) * 8192] * filter[k];
        k++;
      }
      sol[i * 8192 + j] = tmp;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:23:37: error: subscripted value is neither array nor pointer nor vector
   23 |         tmp += orig[i + (-4 + k) * 8192] * filter[k];
      |                                     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:25:13: error: subscripted value is neither array nor pointer nor vector
   25 |       sol[i * 8192 + j] = tmp;
      |             ^

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp = 0;
  int elem;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      tmp = 0;
      k = 0;
      while (k < 9) {
        tmp += orig[i + (-4 + k) * 8192] * filter[k];
        k++;
      }
      sol[i * 8192 + j] = tmp;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:23:37: error: subscripted value is neither array nor pointer nor vector
   23 |         tmp += orig[i + (-4 + k) * 8192] * filter[k];
      |                                     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:25:13: error: subscripted value is neither array nor pointer nor vector
   25 |       sol[i * 8192 + j] = tmp;
      |             ^

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp = 0;
  int elem;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}