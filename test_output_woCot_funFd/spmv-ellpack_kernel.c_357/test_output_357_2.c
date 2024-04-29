<<<<<<< HEAD
Code: #pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
=======
Code: #pragma ACCEL PARAMS ellpack_nzval=auto{4940} ellpack_cols=auto{4940} ellpack_vec=auto{494} ellpack_out=auto{494}:
   User-provided parameters for the function ellpack. The values of these parameters are automatically passed to the function at runtime.

#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
 #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{4}

#pragma ACCEL PARALLEL FACTOR=auto{1}
 #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{16}
 #pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{4}

#pragma ACCEL PARALLEL FACTOR=auto{1}
 #pragma ACCEL PIPELINE auto{off}
#include <math.h>
#pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
<<<<<<< HEAD
  double val;
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
    for (j = 0; j < 32; j++) {
      val = nzval[i * 32 + j];
      sum += val * vec[cols[i * 32 + j]];
    }
    out[i] = sum;
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:4: error: unknown type name ‘Disable’
    2 |    Disable auto-pipelining to avoid excessive area usage.
      |    ^~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:17: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘off’
    2 |    Disable auto-pipelining to avoid excessive area usage.
      |                 ^~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:4: error: stray ‘#’ in program
    4 | 6. #pragma ACCEL PIPELINE auto{off}
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:42: error: expected identifier or ‘(’ before ‘{’ token
    4 | 6. #pragma ACCEL PIPELINE auto{off}
      |                                          ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:4: error: stray ‘#’ in program
    5 | 6. #pragma ACCEL TILE FACTOR=auto{4}
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:42: error: expected identifier or ‘(’ before ‘{’ token
    5 | 6. #pragma ACCEL TILE FACTOR=auto{4}
      |                                          ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:4: error: stray ‘#’ in program
    6 | 6. #pragma ACCEL PARALLEL FACTOR=auto{16}
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:42: error: expected identifier or ‘(’ before ‘{’ token
    6 | 6. #pragma ACCEL PARALLEL FACTOR=auto{16}
      |                                          ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:2: error: stray ‘#’ in program
    7 | #pragma ACCEL PIPELINE auto{off}
      |  ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:2: error: stray ‘#’ in program
    7 | #pragma ACCEL PIPELINE auto{off}
      |  ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:2: error: stray ‘#’ in program
    7 | #pragma ACC
=======
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 32; j++) {
      sum += nzval[(i * 16 + j)] * vec[cols[(i * 16 + j)]];
    }
    out[i] = sum;
  }
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
