Code: ### Body:
 
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 45;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  outer:
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 1; j < 64 - 1; j++) {
      idx = i * 64 + j;
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner_fact:
      for (k = 0; k < 9; k++) {
        int tmp_idx = center + (k / 3 - 1) * 8 + k % 3 - 1;
        sol[idx] += filter[k] * orig[tmp_idx * 64 + j];
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### Body:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### Body:
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:9: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘:’ token
    1 | ### Body:
      |         ^

Please check the code and try again.
Code: ### Body:
 
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 45;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  outer:
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 1; j < 64 - 1; j++) {
      idx = i * 64 + j;
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner_fact:
      for (k = 0; k < 9; k++) {
        int tmp_idx = center + (k / 3 - 1) * 8 + k % 3 - 1;
        sol[idx] += filter[k] * orig[tmp_idx * 64 + j];
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### Body:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### Body:
      |   ^
/root/autodl-tmp/LL