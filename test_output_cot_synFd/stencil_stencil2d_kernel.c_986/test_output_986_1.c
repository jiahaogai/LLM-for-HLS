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
    for (k = 1; k < 33 - 1; k++) {
      i = j * 32 + k;
      row = j == 1 ? 1 : 0;
      col = k == 1 ? 1 : 0;
      flatten_row = row ? 0 : 32;
      flatten_col = col ? 0 : 1;
      idx = row * 32 + col;
      val = orig[i] + filter[idx] * (orig[i - 1 + flatten_col] + orig[i + 1 + flatten_col] + orig[i - 32 + flatten_row] + orig[i + 32 + flatten_row]);
      sol[i] = val;
    }
  }
}