#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long orig_row;
  long sol_row;
  long orig_offset;
  long sol_offset;
  long k_row;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 1;j++) {...} */
  for (j = 1 + 32 - 1;j >= 1;j--) {
    j_col = j << 3;
    orig_row = j << 5;
    sol_row = (j - 1) << 5;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 1;k++) {...} */
    for (k = 1 + 32 - 1;k >= 1;k--) {
      k_col = k << 3;
      k_row = (32 + 1 - 1 - k) << 3;
      orig_offset = orig_row + k_col;
      sol_offset = sol_row + k_col;
      
#pragma ACCEL PARALLEL FACTOR=auto{3}
      loopi:
      for (i = 32 + 1 - 1;i >= 1;i--) {
        i_col = i << 3;
        sol[sol_offset + i_col] = ((C0 * orig[orig_offset + i_col - 1]) + (C1 * (orig[orig_offset + i_col + 1] + orig[orig_offset + i_col] + orig[orig_offset + i_col - 8] + orig[orig_offset + i_col + 8]))) >> 4;
      }
    }
  }
}