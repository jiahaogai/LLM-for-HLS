#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[256];
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 2; k < 39302 - 2; k++) {...} */
  for (k = 2 + 2996; k < 39302 - 2 - 2996; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 2; j < 39300 - 2; j++) {...} */
    for (j = 2 + 2; j < 39300 - 2 - 2; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 2; i < 39304 - 2; i++) {...} */
      for (i = 2 + 1; i < 39304 - 2 - 1; i++) {
        tmp = 0;
        k_col = k - 2;
        j_col = j - 2;
        i_col = i - 2;
        loopk_col:
/* Standardize from: for(idx = 0; idx < 25; idx++) {...} */
        for (idx = 0; idx < 25; idx++) {
          tmp += C0 * (long )orig[i_col][j_col][k_col];
          k_col++;
        }
        loopj_col:
/* Standardize from: for(idx = 0; idx < 25; idx++) {...} */
        for (idx = 0; idx < 25; idx++) {
          tmp += C1 * (long )orig[i_col][j_col][k_col];
          k_col++;
        }
        buf[idx] = tmp;
        tmp = 0L;
        loopidx:
/* Standardize from: for(idx = 0; idx < 25; idx++) {...} */
        for (idx = 0; idx < 25; idx++) {
          tmp += buf[idx];
        }
        sol[i][j][k] = tmp;
      }
    }
  }
}