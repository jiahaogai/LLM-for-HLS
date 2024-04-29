Code: #pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 8191; i++) {
      idx = i * 8 + j;
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        val += filter[k] * orig[(idx - 4) * 8 + k];
      }
      sol[idx] = val;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before ‘-’ token
    2 | - `#pragma ACCEL kernel`
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:3: error: stray ‘`’ in program
    3 | - `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:4: error: stray ‘#’ in program
    3 | - `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:36: error: stray ‘`’ in program
    3 | - `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
      |                                    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:37: error: expected identifier or ‘(’ before ‘:’ token
    3 | - `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
      |                                     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:50: error: stray ‘`’ in program
    3 | - `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
      |                                                  ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:54: error: stray ‘`’ in program
    3 | - `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
      |                                                      ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:3: error: stray ‘`’ in program
    4 | - `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:4: error: stray ‘#’ in program
    4 | - `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:36: error: stray ‘`’ in program
    4 | - `#pragma ACCEL TILE FACTOR=auto{1}