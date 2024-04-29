Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 0 + 1 - 1; j < 8191 + 1 - 1 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
    for (k = 0 + 1 - 1; k < 8191 + 1 - 1 + 1; k++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopk1:
      for (k1 = -1 + 0; k1 < 1 + 0; k1++) {
        
#pragma ACCEL PIPELINE auto{flatten}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loopj1:
        for (j1 = -1 + 0; j1 < 1 + 0; j1++) {
          t += filter[k1 + 1 - 0] * filter[j1 + 1 - 0] * orig[pad + k + k1];
        }
      }
      sol[pad + k] = t;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:31:12: error: ‘k1’ undeclared (first use in this function); did you mean ‘k’?
   31 |       for (k1 = -1 + 0; k1 < 1 + 0; k1++) {
      |            ^~
      |            k
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:35:14: error: ‘j1’ undeclared (first use in this function); did you mean ‘j’?
   35 |         for (j1 = -1 + 0; j1 < 1 + 0; j1++) {
      |              ^~
      |              j

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 0 + 1 - 1; j < 8191 + 1 - 1 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
    for (k = 0 + 1 - 1; k < 8191 + 1 - 1 + 1; k++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk1:
      for (k1 = -1 + 0; k1 <