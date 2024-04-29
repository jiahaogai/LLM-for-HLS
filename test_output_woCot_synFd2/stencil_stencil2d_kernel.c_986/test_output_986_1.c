The `flatten` optimization factor indicates that the loop should be flattened.

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
  for (j = 0; j < 32; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k ... ) */
    for (k = 0; k < 32; k++) {
      i = j * 32 + k;
      row = j == 0 ? 1 : -1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopcol:
      for (col = k == 0 ? 1 : -1; col != 0; col = k == 31 ? 1 : -1) {
        idx = i + col;
        val = 0;
        
#pragma ACCEL PIPELINE auto{flatten}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loopfilter:
        for (int flatten_i = 0; flatten_i < 9; ++flatten_i) {
          flatten_row = flatten_i / 32;
          flatten_col = flatten_i % 32;
          int tmp_idx = idx + flatten_row - row + flatten_col - k;
          val += filter[flatten_i] * orig[tmp_idx];
        }
        sol[i] = val;
      }
    }
  }
}