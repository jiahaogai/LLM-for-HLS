#pragma ACCEL kernel

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
  long idx_up;
  long idx_dw;
  long idx_ul;
  long idx_ur;
  long idx_ll;
  long idx_lr;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k <= 40 + 0; k++) {
     k_col = k;
     k_row = 40 + -1 * k;
     loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j <= 40 + 0; j++) {
      j_col = j;
      j_row = 40 + -1 * j;
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i <= 40 + 0; i++) {
        i_col = i;
        i_row = 40 + -1 * i;
        idx = i_col + 40 * (j_col + 40 * k_col);
        idx_col = i_col + 40 * j_col;
        idx_row = i_row + 40 * j_row;
        idx_up = idx_col + 40 * (j_row);
        idx_dw = idx_col + 40 * (j_row + 40 - 1);
        idx_ul = idx_row + 40 * (i_col);
        idx_ur = idx_row + 40 * (i_col + 40 - 1);
        idx_ll = idx_row + 40 * (1 + i_col + 40 - 1);
        idx_lr = idx_row + 40 * (1 + i_col);
        t = ((((50.0 * orig[idx]) / (40.0 * 40.0)) + C0) * (((50.0 * orig[idx_ll]) / (40.0 * 40.0)) + C0) + C1) * ((((50.0 * orig[idx_ul]) / (40.0 * 40.0)) + C0) * (((50.0 * orig[idx_ur]) / (40.0 * 40.0)) + C0) + C1) + C1;
        sol[idx] = t;
      }
    }
  }
}