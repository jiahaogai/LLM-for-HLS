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
/* Standardize from: for(k = 2; k < 32 + 2; k++) {...} */
  for (k = 2; k < 34; k++) {
     k_col = vthread_col(k, 34);
     k_row = vthread_row(k, 34);
     loopj:
/* Standardize from: for(j = 2; j < 32 + 2; j++) {...} */
    for (j = 2; j < 34; j++) {
      j_col = vthread_col(j, 34);
      j_row = vthread_row(j, 34);
      loopi:
/* Standardize from: for(i = 2; i < 32 + 2; i++) {...} */
      for (i = 2; i < 34; i++) {
        i_col = vthread_col(i, 34);
        i_row = vthread_row(i, 34);
        idx = i_col + j_col + k_col;
        idx_col = i_col - 1 + j_col + k_col;
        idx_row = i_row + j_row - 1 + k_row;
        t = orig[idx] + ((C0 * orig[idx_col]) + (C1 * orig[idx_row]));
        sol[idx] = t;
      }
    }
  }
}