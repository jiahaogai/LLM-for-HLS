#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
  long tmp;
  long tmp_col;
  long C0_2;
  long C1_2;
  long C0_1;
  long C1_1;
  long C0_0;
  long C1_0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopk_1:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj_1:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_1:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        buf = 0;
        tmp_col = i - 1;
        if (tmp_col < 0) {
          tmp_col = 0;
        }
        C0_2 = tmp_col;
        tmp_col = i + 1;
        if (tmp_col > 39) {
          tmp_col = 39;
        }
        C1_2 = tmp_col;
        tmp_col = j - 1;
        if (tmp_col < 0) {
          tmp_col = 0;
        }
        C0_1 = tmp_col;
        tmp_col = j + 1;
        if (tmp_col > 39) {
          tmp_col = 39;
        }
        C1_1 = tmp_col;
        tmp_col = k - 1;
        if (tmp_col < 0) {
          tmp_col = 0;
        }
        C0_0 = tmp_col;
        tmp_col = k + 1;
        if (tmp_col > 39) {
          tmp_col = 39;
        }
        C1_0 = tmp_col;
        k_col = C1_0 * 40 * 40 + C0_0 * 40 + C1_2;
        j_col = C1_1 * 40 + C0_1;
        i_col = C0_2;
        buf += orig[k_col] + orig[j_col] + orig[i_col];
        tmp_col = k - 1;
        if (tmp_col < 0) {
          tmp_col = 0;
        }
        C0 = tmp_col;
        tmp_col = k + 1;
        if (tmp_col > 39) {
          tmp_col = 39;
        }
        C1 = tmp_col;
        loopk_2:
/* Standardize from: for(k = C0; k <= C1; k++) {...} */
        for (k = C0; k <= C1 + 0; k++) {
          tmp_col = j - 1;
          if (tmp_col < 0) {
            tmp_col = 0;
          }
          C0 = tmp_col;
          tmp_col = j + 1;
          if (tmp_col > 39) {
            tmp_col = 39;
          }
          C1 = tmp_col;
          loopj_2:
/* Standardize from: for(j = C0; j <= C1; j++) {...} */
          for (j = C0; j <= C1 + 0; j++) {
            tmp_col = i - 1;
            if (tmp_col < 0) {
              tmp_col = 0;
            }
            C0 = tmp_col;
            tmp_col = i + 1;
            if (tmp_col > 39) {
              tmp_col = 39;
            }
            C1 = tmp_col;
            loopi_2:
/* Standardize from: for(i = C0; i <= C1; i++) {...} */
            for (i = C0; i <= C1 + 0; i++) {
              k_col = C1 * 40 * 40 + j * 40 + i;
              buf -= orig[k_col];
            }
          }
        }
        sol[k_col] = buf;
      }
    }
  }
}