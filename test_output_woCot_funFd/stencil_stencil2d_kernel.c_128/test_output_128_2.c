Code: #pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop `stencil_label3` whole, not in parts.
- `#pragma ACCEL PIPELINE auto{}`: Allow automatic pipelining for the loop `stencil_label3`.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Divide the iterations of the loop `stencil_label3` into chunks of size 8.


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
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 * (k - 4)) + j;
        val += filter[k] * orig[i * 256 + idx];
      }
      sol[i * 256 + j] = val;
    }
  }
}