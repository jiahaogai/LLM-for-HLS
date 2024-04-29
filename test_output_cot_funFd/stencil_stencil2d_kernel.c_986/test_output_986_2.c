#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flatten_row;
  int flatten_col;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k ... ) */
    for (k = 1; k < 33; k++) {
      i = k + ((j - 1) * 32);
      row = k - 1;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopcol:
      for (col = j - 1; col < 32 + (j - 1); col++) {
        idx = col + ((row - 1) * 32);
        val = 0;
        
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{32}
        loopfilter:
        for (filter_idx = 0; filter_idx < 9; filter_idx++) {
          flatten_row = row + ((filter[filter_idx] - 1) / 32);
          flatten_col = col + ((filter[filter_idx] - 1) % 32);
          val += orig[flatten_row * 32 + flatten_col] * filter[filter_idx];
        }
        sol[idx] = val;
      }
    }
  }
}