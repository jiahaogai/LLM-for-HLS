#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int idx_orig;
  int idy_orig;
  int t;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    inner:
    for (j = 0; j < 256; j++) {
      t = 0;
      inner_1:
      for (k = 0; k < 9; k++) {
        idx = i + (-1 + k);
        idy = j + (-1 + k);
        if (idx >= 0 && idx < 256 && idy >= 0 && idy < 256) {
          idx_orig = idx * 256 + idy;
          t += ((orig[idx_orig]) * (filter[k])) ;
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}