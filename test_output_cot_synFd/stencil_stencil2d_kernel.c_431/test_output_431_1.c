#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int idx;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      flit = 0;
      
#pragma ACCEL PARALLEL reduction = flit FACTOR=auto{16}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = i + ((k / 3) - 1);
        int bound_check = (k_col > -1) && (k_col < 256);
        int src_check = (k % 3) != 4;
        if (bound_check && src_check) {
          int src_idx = k_col * 256 + j;
          flit += filter[k] * orig[src_idx];
        }
      }
      sol[idx] = flit;
    }
  }
}