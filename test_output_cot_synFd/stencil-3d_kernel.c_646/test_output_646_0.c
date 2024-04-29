#pragma ACCEL kernel

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
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 0; k < 40; k++) {...} */
  for (k = 0l; k <= 39l; k++) {
     k_col = -1l;
     i_col = -1l;
     j_col = -1l;
     k_row = 40l;
     i_row = 40l;
     j_row = 40l;
     loop_j:
/* Standardize from: for(j = 0; j < 40; j++) {...} */
    for (j = 0l; j <= 39l; j++) {
      loop_i:
/* Standardize from: for(i = 0; i < 40; i++) {...} */
      for (i = 0l; i <= 39l; i++) {
        idx_col = ((k_col + 1l) * 40l * 40l) + ((i_col + 1l) * 40l) + j_col + 1l;
        idx_row = ((k_row + 1l) * 40l * 40l) + ((i_row + 1l) * 40l) + j_row + 1l;
        idx_in = (k * 40l * 40l) + (i * 40l) + j;
        idx = min(idx_col,idx_row);
        t = orig[idx_in] + ((C0 * (orig[idx_col] + orig[idx_row])) / (C1 + (((long )2) * C1)));
        sol[idx] = t;
      }
      i_col += 1l;
      if (i_col == 39l) {
        i_row += 1l;
        i_col = i_row;
      }
    }
    j_col += 1l;
    if (j_col == 39l) {
      j_row += 1l;
      j_col = j_row;
    }
    k_col += 1l;
    if (k_col == 39l) {
      k_row += 1l;
      k_col = k_row;
    }
  }
}