Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 8191; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        result += orig[i + (-1 + k) + (j + (-1 + k)) * 8192] * filter[k];
      }
      sol[i + j * 8192] = result;
      result = 0;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:162: warning: missing terminating ' character
    1 | #pragma ACCEL PIPELINE auto{off}: Do not automatically pipeline the loops inside the function.
      |                                                                                                                                                                  ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before ‘-’ token
    2 | - #pragma ACCEL ARRAY FACTOR=auto{1}: Do not automatically pipeline the 'orig' array.
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:3: error: stray ‘#’ in program
    2 | - #pragma ACCEL ARRAY FACTOR=auto{1}: Do not automatically pipeline the 'orig' array.
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:37: error: expected identifier or ‘(’ before ‘:’ token
    2 | - #pragma ACCEL ARRAY FACTOR=auto{1}: Do not automatically pipeline the 'orig' array.
      |                                     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:73: warning: multi-character character constant [-Wmultichar]
    2 | - #pragma ACCEL ARRAY FACTOR=auto{1}: Do not automatically pipeline the 'orig' array.
      |                                                                         ^~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:3: error: stray ‘#’ in program
    3 | - #pragma ACCEL ARRAY FACTOR=auto{1}: Do not automatically pipeline the 'sol' array.
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:37: error: expected identifier or ‘(’ before ‘:’ token
    3 | - #pragma ACCEL ARRAY FACTOR=auto{1}: Do not automatically pipeline the 'sol' array.
      |                                     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:73: warning: multi-character character constant [-Wmultichar]
    3 | - #pragma ACCEL ARRAY FACTOR=auto{1}: Do not automatically pipeline the 'sol' array.
      |                                                                         ^~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:3: error: stray ‘#’ in program
    4 | - #pragma ACCEL ARRAY FACTOR=auto{8}: The 'filter' array is smaller than the automatic chunk size, so explicitly specify a smaller chunk size.