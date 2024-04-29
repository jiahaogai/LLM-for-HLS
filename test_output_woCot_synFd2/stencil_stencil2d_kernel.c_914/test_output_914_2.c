Code: #pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        val += filter[k] * orig[idx + ((k - 4) * 256)];
      }
      sol[idx] = val;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before numeric constant
    2 | 9. `#pragma ACCEL kernel`
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:4: error: stray ‘`’ in program
    2 | 9. `#pragma ACCEL kernel`
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:5: error: stray ‘#’ in program
    2 | 9. `#pragma ACCEL kernel`
      |     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:42: error: stray ‘`’ in program
    2 | 9. `#pragma ACCEL kernel`
      |                            ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:43: error: expected identifier or ‘(’ before ‘:’ token
    2 | 9. `#pragma ACCEL kernel`
      |                             ^

Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        val += filter[k] * orig[idx + ((k - 4) * 256)];
      }
//#pragma ACCEL PIPELINE auto{off}
        sol[idx] = val;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before numeric constant
    2 | 9. `#pragma ACCEL kernel`
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: