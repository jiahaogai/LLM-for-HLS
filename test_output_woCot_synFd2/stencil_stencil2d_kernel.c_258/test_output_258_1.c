Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 45;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 1; j < 8186; j++) {
      idx = (8192 + center - (i + center)) % 8192 + (8186 + center - j) % 8186;
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sol[idx] += filter[k] * orig[idx + kernel_offsets[k]];
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:25:44: error: ‘kernel_offsets’ undeclared (first use in this function)
   25 |         sol[idx] += filter[k] * orig[idx + kernel_offsets[k]];
      |                                            ^~~~~~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:25:44: note: each undeclared identifier is reported only once for each function it appears in

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 45;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 1; j < 8186; j++) {
      idx = (8192 + center - (i + center)) % 8192 + (8186 + center - j) % 8186;
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sol[idx] += filter[k] * orig[idx + kernel_offsets[k]];
      }
    }
  }
}