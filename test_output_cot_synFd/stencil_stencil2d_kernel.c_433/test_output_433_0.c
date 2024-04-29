#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_row:
/* Standardize from: for(i = 1; i < 32 + 1 - 4; i++) {...} */
  for (i = 1 + 4 - 1; i < 32 + 1 - 4; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_col:
/* Standardize from: for(j = 1; j < 32 + 1 - 4; j++) {...} */
    for (j = 1 + 4 - 1; j < 32 + 1 - 4; j++) {
      i_col = i - 1 + 4 * (1 - 1);
      j_col = j - 1 + 4 * (1 - 1);
      sol[i + 32 * j] = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
      for (k = 0; k < 9; k++) {
        k_col = k - 4 + 32 * (1 - 1);
        flit = orig[i_col + 32 * k_col] * filter[k];
        sol[i + 32 * j] += flit;
      }
    }
  }
}