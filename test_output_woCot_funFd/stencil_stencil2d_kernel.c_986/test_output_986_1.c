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
      row = i << 8;
      flatten_row = (i << 6) | (k + 4 - (i << 5));
      loopi:
/* Standardize from: for(i ... ) */
      for (i = 0; i < 8; i++) {
        col = ((k + 4) & 31) << 3;
        flatten_col = (k + 4) & 31;
        idx = row + col + flatten_col;
        val = orig[idx] * filter[k];
        sol[idx] = val;
      }
    }
  }
}