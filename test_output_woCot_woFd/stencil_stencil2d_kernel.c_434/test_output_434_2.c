- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the flattened loop whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{2}`: Execute the flattened loop iterations concurrently, with a parallel factor of 2.
- `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline the stencil loop.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the stencil loop whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute the stencil loop iterations sequentially, not concurrently.

#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      inner:
      for (k = -4; k < 5; k++) {
        k_col = k + j;
        if (k_col < 0) {
          k_col += 8192;
        }
        else {
          if (k_col > 8191) {
            k_col -= 8192;
          }
        }
        i_col = i - 4 + k;
        if (i_col < 0) {
          i_col += 8192;
        }
        else {
          if (i_col > 8191) {
            i_col -= 8192;
          }
        }
        sum += filter[k + 4] * orig[i_col * 8192 + k_col];
      }
      sol[i * 8192 + j] = sum;
    }
  }
}