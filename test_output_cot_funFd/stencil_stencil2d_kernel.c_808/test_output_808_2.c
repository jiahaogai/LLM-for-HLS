#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int fidx;
  int val;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{31}
  sp_loop:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    wp_loop:
    for (j = 0; j < 64 + 2; j++) {
      val = 0;
      sp_loop:
      for (k = -1; k <= 1; k++) {
        fidx = 4 * k + 4;
        idx = (64 + 2) * (i - 1) + (j - 1) + k;
        val += filter[fidx] * orig[idx];
      }
      sol[j + (i - 1) * (64 + 2)] = val;
    }
  }
}