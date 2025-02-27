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
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
     k_col = v_idx_col[k];
     k_row = v_idx_row[k];
     loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      j_col = v_idx_col[j];
      j_row = v_idx_row[j];
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i > 32L; i--) {
        i_col = v_idx_col[i];
        i_row = v_idx_row[i];
        idx = i_col * I + i_row;
        idx_col = i_col * C0;
        idx_row = i_row * C1;
        t = orig[idx] + ((+1 * (orig[idx_col + idx_row] + orig[idx_col + 1 + idx_row] + orig[idx_col + 2 + idx_row] + orig[idx_col + C1 + idx_row] + orig[idx_col + 1 + C1 + idx_row] + orig[idx_col + 2 + C1 + idx_row])) / 6);
        sol[idx] = t;
      }
    }
  }
}