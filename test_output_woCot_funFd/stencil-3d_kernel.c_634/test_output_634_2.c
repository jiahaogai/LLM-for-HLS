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
  long idx_in;
  long t;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 0; k < 40; k++) {...} */
  for (k = 0L; k < 40L; k++) {
     k_col = k;
     i_col = 0L;
     loop_j:
/* Standardize from: for(j = 0; j < 40; j++) {...} */
    for (j = 0L; j < 40L; j++) {
      j_col = j;
      i_row = i_col + 1L;
      loop_i:
/* Standardize from: for(i = 0; i < 40; i++) {...} */
      for (i = i_col; i < 40L; i++) {
        j_row = j_col + 1L;
        idx = i + (j + (k * 40L)) * 40L;
        idx_col = i_col + (j_col * 40L);
        idx_row = i_row + (j_row * 40L);
        idx_in = i + (j * 40L) + k * 1600L;
        t = ((((50L * orig[idx_in]) - (16L * orig[idx_col])) - (16L * orig[idx_row])) - (4L * orig[idx])) / 160L;
        sol[idx] = t;
      }
      i_col = i;
    }
    k_row = k_col + 1L;
  }
}