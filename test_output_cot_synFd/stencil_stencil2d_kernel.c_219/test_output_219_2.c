Code: ### Function Body:
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 33 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
    for (k = 1; k < 33 - 1; k++) {
      idx = (((32 + 2) * (k - 1)) + (j - 1));
      val = ((filter[0] * orig[idx]) + (filter[1] * (orig[idx + 1] + orig[idx - 1])) + (filter[2] * orig[idx + 2]) + (filter[3] * (orig[idx + 3] + orig[idx - 3])) + (filter[4] * (orig[idx + 4] + orig[idx - 4])) + (filter[5] * (orig[idx + 5] + orig[idx - 5])) + (filter[6] * (orig[idx + 6] + orig[idx - 6])) + (filter[7] * (orig[idx + 7] + orig[idx - 7])) + (filter[8] * orig[idx + 8]));
      sol[idx] = val;
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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 33 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
    for (k = 1; k < 33 - 1; k++) {
      idx = (((32 + 2) * (k - 1)) + (j - 1));
      val = ((filter[0] * orig[idx]) + (filter[1] * (orig[idx + 1] + orig[idx - 1])) + (filter[2] * orig[idx + 2]) + (filter[3