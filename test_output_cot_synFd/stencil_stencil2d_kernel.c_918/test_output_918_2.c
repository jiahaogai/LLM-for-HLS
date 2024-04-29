#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int idx;
  int flit;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loopj:
/* Standardize from: for(j = 1;j < 33 - 1;j++) {...} */
  for (j = 0 + 1; j < 33 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopk_col:
    for (k_col = 0; k_col < 32 + 1; k_col++) {
      idx = (j * (32 + 1)) + k_col;
      flit = 0;
      
#pragma ACCEL PARALLEL reduction=flit FACTOR=auto{32}
      loopk:
      for (k = 1; k < 33 - 1; k++) {
        idx = (j * (32 + 1)) + k_col + k * 32;
        flit += orig[idx] * filter[k];
      }
      sol[idx] = flit;
    }
  }
}