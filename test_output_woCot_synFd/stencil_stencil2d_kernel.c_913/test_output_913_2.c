Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8; j++) {
      inner:
      for (k = 0; k < 8; k++) {
        result = ((filter[0] * orig[i - 8192 + (-8)]) + (filter[1] * orig[i - 8192 + (-7)]) + (filter[2] * orig[i - 8192 + (-6)]) + (filter[3] * orig[i - 8192 + (-5)]) + (filter[4] * orig[i - 8192 + (-4)]) + (filter[5] * orig[i - 8192 + (-3)]) + (filter[6] * orig[i - 8192 + (-2)]) + (filter[7] * orig[i - 8192 + (-1)]) + (filter[8] * orig[i - 8192 + 0]) + (filter[1] * orig[i - 8192 + 1]) + (filter[2] * orig[i - 8192 + 2]) + (filter[3] * orig[i - 8192 + 3]) + (filter[4] * orig[i - 8192 + 4]) + (filter[5] * orig[i - 8192 + 5]) + (filter[6] * orig[i - 8192 + 6]) + (filter[7] * orig[i - 8192 + 7]) + (filter[8] * orig[i - 8192 + 8])) >> 12;
        sol[i] = result;
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before numeric constant
    2 | 5. #pragma ACCEL PIPELINE auto{}
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:4: error: stray ‘#’ in program
    2 | 5. #pragma ACCEL PIPELINE auto{}
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:33: error: expected identifier or ‘(’ before ‘:’ token
    2 | 5. #pragma ACCEL PIPELINE auto{}
      |                               ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:4: error: stray ‘#’ in program
    3 | 6. #pragma ACCEL TILE FACTOR=auto{1}
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:41: error: expected identifier or ‘(’ before ‘:’ token
    3 | 6. #pragma ACCEL TILE FACTOR=auto{1}
      |                                   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:4: error: stray ‘#’ in program
    4 | 7. #pragma ACCEL PARALLEL FACTOR=auto{2}
      |    ^
/root/autodl-tmp/LLM