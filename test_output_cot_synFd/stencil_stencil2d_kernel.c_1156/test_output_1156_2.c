Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 128 - 1; j++) {
      s = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        idx = (i + kernel_off_d[k]) * 128 + j + kernel_off_a[k];
        s += orig[idx] * filter[k];
      }
      sol[i * 128 + j] = s;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:29:22: error: ‘kernel_off_d’ undeclared (first use in this function)
   29 |         idx = (i + kernel_off_d[k]) * 128 + j + kernel_off_a[k];
      |                      ^~~~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:29:22: note: each undeclared identifier is reported only once for each function it appears in
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:29:113: error: ‘kernel_off_a’ undeclared (first use in this function)
   29 |         idx = (i + kernel_off_d[k]) * 128 + j + kernel_off_a[k];
      |                                                                 ^~~~~~~~~~~~

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 128; j++) {
      s = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (((i + kernel_off_d[k]) < 64) ? (i + kernel_off_d[k]) : (i + kernel_off_d[k]) - 64) * 128 + ((j + kernel_off_a[k]) < 128 ? (j + kernel_off_a[k]) : (j + kernel_off_a[k]) - 128);
        s += filter[k] * orig[idx];
      }
      sol[i * 128 + j] = s;
    }
  }
}
Error: /root/autodl-