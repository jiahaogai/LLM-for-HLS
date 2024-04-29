Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8188; j++) {
      result = ((8192 * (j - 1)) + i) * 4;
      sol[result - 4] = ((filter[0] * orig[result - 4]) + (filter[1] * orig[result - 3]) + (filter[2] * orig[result - 2]) + (filter[3] * orig[result - 1]) + (filter[4] * orig[result]) + (filter[5] * orig[result + 1]) + (filter[6] * orig[result + 2]) + (filter[7] * orig[result + 3]) + (filter[8] * orig[result + 4])) / 8192;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8184; j++) {
      result = ((8192 * (j - 1)) + i) * 4;
      sol[result + 4] = ((filter[0] * orig[result - 4]) + (filter[1] * orig[result - 3]) + (filter[2] * orig[result - 2]) + (filter[3] * orig[result - 1]) + (filter[4] * orig[result]) + (filter[5] * orig[result + 1]) + (filter[6] * orig[result + 2]) + (filter[7] * orig[result + 3]) + (filter[8] * orig[result + 4])) / 8192;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before numeric constant
    2 | 6. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:4: error: stray ‘`’ in program
    2 | 6. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:5: error: stray ‘#’ in program
    2 | 6. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
      |     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:38: error: stray ‘`’ in program
    2 | 6. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
      |                                      ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:40: error: expected identifier or ‘(’ before ‘-’ token
    2 | 6. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
      |                                        ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:4: error: stray ‘`’ in program
    3 | 7. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep this loop whole