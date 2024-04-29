Code: ### Function Body:
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 4; i < 8192 - 4; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 4; j < 8192 - 4; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = i * 8192 + j + (-4 + k) * 8192;
        val += filter[k] * orig[idx];
      }
      sol[i * 8192 + j] = val;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### Function Body:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### Function Body:
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:5: error: unknown type name ‘Function’; did you mean ‘union’?
    1 | ### Function Body:
      |     ^~~~~~~~
      |     union
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:18: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘:’ token
    1 | ### Function Body:
      |                  ^

Please check the code and try again.
Code: ### Function Body:
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = i * 8192 + j + (-4 + k) * 8192;
        val += filter[k] * orig[idx];
      }
      sol[i * 8192 + j] = val;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### Function Body:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### Function Body:
      |   ^
/root/autodl-tmp/LLM/LLM-for