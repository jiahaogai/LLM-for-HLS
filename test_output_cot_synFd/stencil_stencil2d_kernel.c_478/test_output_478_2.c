#pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{4}

#pragma ACCEL PARALLEL FACTOR=auto{18}
void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    inner:
    for (j = 0; j < 256; j++) {
      val = 0;
      filter:
      for (k = 0; k < 9; k++) {
        idx = (256 * (k - 4)) + j;
        val += orig[i * 256 + idx] * filter[k];
      }
      sol[i * 256 + j] = val;
    }
  }
}