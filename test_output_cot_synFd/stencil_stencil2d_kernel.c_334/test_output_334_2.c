Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 45;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 8188; j++) {
      idx = (i - 1) * 8188 + j - 1;
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        int cur = idx + distance[k];
        sol[idx] += filter[k] * orig[cur];
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:32:44: error: ‘distance’ undeclared (first use in this function)
   32 |         sol[idx] += filter[k] * orig[idx + distance[k]];
      |                                            ^~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:32:44: note: each undeclared identifier is reported only once for each function it appears in

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 45;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 8188; j++) {
      idx = (i - 1) * 8188 + j - 1;
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        int cur = idx + distance[k];
        sol[idx] += filter[k] * orig[cur];
      }
    }
  }
}