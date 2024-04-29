Code: #pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int off;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopi:
    for (i = 1; i < 8191; i++) {
      sum = 0;
      off = -4 + filter[0];
      loopk:
      for (k = 0; k < 9; k++) {
        sum += orig[i + off] * filter[k];
        off = -4 + filter[k + 1];
      }
      sol[j * 8192 + i] = sum;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:20: warning: extra tokens at end of #include directive
    1 | #include "models.h"
      |                    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:10: fatal error: models.h: No such file or directory
    1 | #include "models.h"
      |          ^~~~~~~~~~
compilation terminated.

Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int off;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopi:
    for (i = 1; i < 8191; i++) {
      sum = 0;
      off = -4 + filter[0];
      loopk:
      for (k = 0; k < 9; k++) {
        sum += orig[i + off] * filter[k];
        off = -4 + filter[k + 1];
      }
      sol[j * 8192 + i] = sum;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:20: warning: extra tokens at end of #include directive
    1 | #include "models.h"
      |                    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:10: fatal error: models.h: No such file or directory
    1 | #include "models.h"
      |          ^~~~~~~~~~
compilation terminated.

Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int off;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i =