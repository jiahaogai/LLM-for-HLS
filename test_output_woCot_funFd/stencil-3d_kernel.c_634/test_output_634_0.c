#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}
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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 0; k < 40; k++) {...} */
  for (k = 0L; k <= 39L - 1L; k++) {
     k_col = k * 64L;
     loop_j:
/* Standardize from: for(j = 0; j < 64; j++) {...} */
    for (j = 0L; j <= 63L - 1L; j++) {
      j_col = j * 4L;
      loop_i:
/* Standardize from: for(i = 0; i < 40; i++) {...} */
      for (i = 0L; i <= 39L - 1L; i++) {
        i_col = i * 64L;
        t = ((C0 * (orig[i_col + j_col + k_col] + orig[i_col + 1L + j_col + k_col] + orig[i_col + 2L + j_col + k_col] + orig[i_col + 3L + j_col + k_col])) + (C1 * (orig[i_col + j_col + k_col + 64L] + orig[i_col + 1L + j_col + k_col + 64L] + orig[i_col + 2L + j_col + k_col + 64L] + orig[i_col + 3L + j_col + k_col + 64L])));
        sol[i_col + j_col + k_col] = t;
      }
    }
  }
}