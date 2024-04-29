#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int idx;
  int flatten_idx;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      flatten_idx = i * 256 + j;
      idx = i * 16 + j;
      sol[flatten_idx] = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{16}
      inner:
      for (k = 0; k < 16; k++) {
        k_col = k * 256;
        sol[flatten_idx] += filter[k] * orig[idx + k_col];
      }
    }
  }
}