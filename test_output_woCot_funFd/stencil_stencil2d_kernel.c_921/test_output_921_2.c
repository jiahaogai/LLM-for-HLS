Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 1; j < 128 - 1; j++) {
      int idx = i * 128 + j;
      int val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        val += filter[k] * orig[idx + neighbor[k]];
      }
      sol[idx] = val;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:32:39: error: ‘neighbor’ undeclared (first use in this function)
   32 |         val += filter[k] * orig[idx + neighbor[k]];
      |                                       ^~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:32:39: note: each undeclared identifier is reported only once for each function it appears in

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 1; j < 128 - 1; j++) {
      int idx = i * 128 + j;
      int val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{16}
      inner:
      for (k = 0; k < 9; k++) {
        val += filter[k] * orig[idx + neighbor[k]];
      }
      sol[idx] = val;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:32:39: error: ‘neighbor’ undeclared (first use in this function)
   32 |         val += filter[k] * orig[idx + neighbor[k]];
      |                                       ^~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:32:39: note: each undeclared identifier is reported only once for each function it appears in

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192