#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{30}

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
  loopj_col:
/* Standardize from: for(j_col = 1;j_col < 40;j_col++) {...} */
  for (j_col = 1; j_col < 40; j_col++) {
    loopk_col:
/* Standardize from: for(k_col = 1;k_col < 40;k_col++) {...} */
    for (k_col = 1; k_col < 40; k_col++) {
      i_col = 1 - 1;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_col:
      while (1) {
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        loopj_row:
/* Standardize from: for(j_row = 1;j_row <= 39;j_row++) {...} */
        for (j_row = 1; j_row <= 39; j_row++) {
          k_row = 1 - 1;
          
#pragma ACCEL PIPELINE auto{}
          
#pragma ACCEL TILE FACTOR=auto{1}
          loopk_row:
          while (1) {
            idx_col = 40 * (1 - 1) + 1;
            idx_row = 40 * (1 - 1) + 1;
            t = 0;
            loopk:
/* Standardize from: for(k = 1;k <= 39;k++) {...} */
            for (k = 1; k <= 39; k++) {
              idx = 40 * k + 1;
              t += orig[idx_col + k] + orig[idx_row + k] + orig[idx + k_col] - orig[idx];
            }
            sol[idx_col + k_row] = t;
            k_row++;
          }
          k_row = 40 - 1;
        }
        i_col++;
        if (i_col == 40) {
          break;
        }
      }
      k_col = 40 - 1;
    }
    j_col++;
    if (j_col == 40) {
      break;
    }
  }
}