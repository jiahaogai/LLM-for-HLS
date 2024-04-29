#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long k_row;
  long i_row;
  long idx;
  long idx_col;
  long idx_row;
  long idx_in;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loop_k:
/* Standardize from: for(k = 2; k < 32 + 2; k++) {...} */
  for (k = 2; k <= 34; k++) {
     k_col = k;
     i_col = 2;
     loop_j:
/* Standardize from: for(j = 2; j < 32 + 2; j++) {...} */
    for (j = 2; j <= 34; j++) {
      i_row = i_col;
      k_row = k_col;
/* Standardize from: for(i = 2; i < 32 + 2; i++) {...} */
      loop_i:
      for (i = 2; i <= 34; i++) {
        idx_in = i_row * (34 + 2) + k_row;
        t = orig[idx_in];
        idx_col = i * (34 + 2) + j;
        idx_row = j * (34 + 2) + i;
        sol[idx_col] = t + C0 * (orig[idx_row] + orig[idx_col]);
        sol[idx_row] = t + C1 * (orig[idx_row] + orig[idx_col]);
      }
      i_row += 34;
    }
    k_col += 34;
  }
}