#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PIPELINE auto{flatten}

#pragma ACCEL TILE FACTOR=auto{2}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long k_row;
  long j_row;
  long i_row;
  long idx;
  long idx_col;
  long idx_row;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k <= 40 + 0; k++) {
     k_col = (40 + 0) - k;
     k_row = (40 + 0) - k;
     loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j <= 40 + 0; j++) {
      j_col = (40 + 0) - j;
      j_row = (40 + 0) - j;
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i <= 40 + 0; i++) {
        i_col = (40 + 0) - i;
        i_row = (40 + 0) - i;
        idx = i + (j + (k * 40)) * 40;
        idx_col = i_col + (j_col + (k_col * 40)) * 40;
        idx_row = i_row + (j_row + (k_row * 40)) * 40;
        t = orig[idx] + 2 * (orig[idx_col] + orig[idx_row]) - orig[idx_col + 40];
        sol[idx] = t;
      }
    }
  }
}