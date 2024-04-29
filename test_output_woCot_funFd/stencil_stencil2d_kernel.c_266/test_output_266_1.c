<<<<<<< HEAD
Code: #pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
=======
Code: `
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int sum;
  int off;
=======
//#pragma scop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
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
=======
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      sol[i * 8192 + j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{62}
      for (k = 0; k < 9; k++) {
        sol[i * 8192 + j] += filter[k] * orig[(i + pad[0]) * 8192 + (j + pad[1]) * 9 + k];
      }
    }
  }
//#pragma endscop
}
`
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
