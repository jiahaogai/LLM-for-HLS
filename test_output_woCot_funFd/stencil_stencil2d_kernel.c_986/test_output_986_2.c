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
  for (j = 0; j < 256; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k ... ) */
    for (k = 0; k < 9; k++) {
      i = j - 4 + ((k + 4) >> 5);
      row = i * 64;
      flatten_row = row * 2;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopidx:
/* Standardize from: for(idx ... ) */
      for (idx = 0; idx < 64; idx++) {
        flatten_col = flatten_row + ((idx + 4) >> 5);
        col = flatten_col * 2;
        val = orig[row + idx] * filter[k];
        sol[flatten_col + idx] += val;
      }
    }
  }
}