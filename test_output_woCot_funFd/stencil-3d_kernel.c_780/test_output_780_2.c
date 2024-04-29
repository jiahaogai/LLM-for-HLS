Code: #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long k_row;
  long i_row;
  long j_row;
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
      j_col = j;
      i_row = 2;
      loop_i:
/* Standardize from: for(i = 2; i < 32 + 2; i++) {...} */
      for (i = 2; i <= 34; i++) {
        i_row = i;
        idx_col = k_col * (34 + 2) + i_col;
        idx_row = i_row * (34 + 2) + j_col;
        idx = idx_col * (34 + 2) + idx_row;
        t = orig[idx] + ((C0 * (orig[idx_col + -1] + orig[idx_col + 1])) + (C1 * (orig[idx_row + -1] + orig[idx_row + 1])));
        sol[idx] = t;
      }
      i_row = 34 + 1;
    }
    k_row = 34 + 1;
  }
}