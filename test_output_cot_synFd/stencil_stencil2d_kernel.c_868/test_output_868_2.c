#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 0;j < 128;j++) {...} */
  for (j = 0; j <= 127; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 0;k < 64;k++) {...} */
    for (k = 0; k <= 63; k++) {
      idx = (((128 + 2) * (64 + 2)) * j) + ((64 + 2) * k) + 128;
      center = orig[idx];
      kidx:
/* Standardize from: for(k = 0;k < 9;k++) {...} */
      for (k = 0; k <= 8; k++) {
        int tmp_idx = (((128 + 2) * (64 + 2)) * ((j + ((k - 4) > -1 ? 1 : 0) + 128)) + ((64 + 2) * (k - 4) + 16)) + 128;
        sol[idx] = center + filter[k] * (tmp_idx < 0 ? 0 : tmp_idx > 8191 ? 0 : orig[tmp_idx]);
      }
    }
  }
}