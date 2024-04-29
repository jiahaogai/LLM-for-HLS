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
  long val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1; k < 40 + 0; k++) {
     k_col = (40 * 2 * 2) + 1 - k;
     i_col = 40 + 1 - k_col;
    loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1; j < 40 + 0; j++) {
      j_col = (40 * 2 * 2) + 1 - j;
      i_row = 40 + 1 - j_col;
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1; i < 40 + 0; i++) {
        i_row = 40 + 1 - i;
        idx_col = i_col * 40 + j_col;
        idx_row = i_row * 40 + j_col;
        idx = idx_col * 40 + k_col;
        val = orig[idx] + ((k_col == 1 ? 1 : 0) * (i_col == 1 ? 1 : 0) * (j_col == 1 ? 1 : 0)) * ((((i_row - 1) < 1 ? 1 : (i_row - 1))) < 40 ? ((((j_row - 1) < 1 ? 1 : (j_row - 1))) < 40 ? orig[idx_row - 1 - 1 * 40] : 0) : 0) + ((k_col == 1 ? 1 : 0) * (i_col == 1 ? 1 : 0) * (j_col == 1 ? 1 : 0)) * ((((i_row - 1) < 1 ? 1 : (i_row - 1))) < 40 ? ((((j_row + 0) < 40 ? (j_row + 0) : 40)) < 40 ? orig[idx_row - 1 + 0 * 40] : 0) : 0) + ((k_col == 1 ? 1 : 0) * (i_col == 1 ? 1 : 0) * (j_col == 1 ? 1 : 0)) * ((((i_row + 0) < 40 ? (i_row + 0) : 40)) < 40 ? ((((j_row - 1) < 1 ? 1 : (j_row - 1))) < 40 ? orig[idx_row + 0 - 1 * 40] : 0) : 0) + ((k_col == 1 ? 1 : 0) * (i_col == 1 ? 1 : 0) * (j_col == 1 ? 1 : 0)) * ((((i_row + 0) < 40 ? (i_row + 0) : 40)) < 40 ? ((((j_row + 0) < 40 ? (j_row + 0) : 40)) < 40 ? orig[idx_row + 0 + 0 * 40] : 0) : 0) + ((k_col == 40 ? 1 : 0) * (i_col == 1 ? 1 : 0) * (j_col == 1 ? 1 : 0)) * ((((i_row - 1) < 1 ? 1 : (i_row - 1))) < 40 ? ((((j_row - 1) < 1 ? 1 : (j_row - 1))) < 40 ? orig[idx_row - 1 - 1 * 40] : 0) : 0) + ((k_col == 40 ? 1 : 0) * (i_col == 1 ? 1 : 0) * (j_col == 1 ? 1 : 0)) * ((((i_row - 1) < 1 ? 1 : (i_row - 1))) < 40 ? ((((j_row + 0) < 40 ? (j_row + 0) : 40)) < 40 ? orig[idx_row - 1 + 0 * 40] : 0) : 0) + ((k_col == 40 ? 1 : 0) * (i_col == 1 ? 1 : 0) * (j_col == 1 ? 1 : 0)) * ((((i_row + 0) < 40 ? (i_row + 0) : 40)) < 40 ? ((((j_row - 1) < 1 ? 1 : (j_row - 1))) < 40 ? orig[idx_row + 0 - 1 * 40] : 0) : 0) + ((k_col == 40 ? 1 : 0) * (i_col == 1 ? 1 : 0) * (j_col == 1 ? 1 : 0)) * ((((i_row + 0) < 40 ? (i_row + 0) : 40)) < 40 ? ((((j_row + 0) < 40 ? (j_row + 0) : 40)) < 40 ? orig[idx_row + 0 + 0 * 40] : 0) : 0);
        sol[idx] = val;
      }
    }
  }
}