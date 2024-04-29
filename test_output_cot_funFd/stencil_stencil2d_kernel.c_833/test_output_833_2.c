#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  int left;
  int right;
  int top;
  int bottom;
  int flatten_idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 8; j < 8184; j += 8) {
      center = orig[i * 8192 + j];
      left = orig[i * 8192 + j - 1];
      right = orig[i * 8192 + j + 1];
      top = orig[(i - 1) * 8192 + j];
      bottom = orig[(i + 1) * 8192 + j];
      flatten_idx = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      inner:
      for (k = 0; k < 9; k++) {
        idx = filter[k] * center + (1 - filter[k]) * (left + right + top + bottom - 4 * center);
        sol[flatten_idx] = idx;
        flatten_idx += 8192;
      }
    }
  }
}