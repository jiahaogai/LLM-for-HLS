#pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 4096; i < 8192 - 4096; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64; j++) {
      idx = i * 64 + j;
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
      inner:
      for (k = -4; k < 5; k++) {
        val += filter[k + 4] * orig[idx + k * 64];
      }
      sol[idx] = val;
    }
  }
}