The HLS tool automatically synthesizes a hardware implementation for the function based on the pragma directives and the function's code.

The pragma directives used in this function are:

 
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 337; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 337; j++) {
      sol[i * 337 + j] = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      int tmp_sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      int tmp_src[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      int tmp_dst[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      int k;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        tmp_src[k] = orig[(i - 1 + 336) * 337 + j - 1 + 336 + k];
      }
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        tmp_dst[k] = tmp_src[k] + filter[k];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        tmp_sum += tmp_dst[k];
      }
      sol[i * 337 + j] = tmp_sum;
    }
  }
}