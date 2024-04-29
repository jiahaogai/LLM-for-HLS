#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
  long delta;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 40;j++) {...} */
  for (j = 1; j <= 39; j++) {
    long j_col_0 = 40 * j;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 40;k++) {...} */
    for (k = 1; k <= 39; k++) {
      long k_col_0 = j_col_0 + k;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 40;i++) {...} */
      for (i = 1; i <= 39; i++) {
        long i_col_0 = k_col_0 * 40 + i;
        long sum = ((C0 * orig[i_col_0]) + (C1 * (orig[k_col_0 + 1] + orig[k_col_0 - 1] + orig[i_col_0 + 40] + orig[i_col_0 - 40]))) / (C1 * 8);
        buf = sum;
        delta = sum - orig[i_col_0];
        orig[i_col_0] = sum;
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loopj_col:
        for (j_col = j - 1; j_col <= j + 1; j_col++) {
#pragma ACCEL PARALLEL FACTOR=auto{1}
          loopk_col:
          for (k_col = k - 1; k_col <= k + 1; k_col++) {
            i_col = k_col * 40 + i;
            if ((((j_col >= 1) && (j_col <= 39)) && ((k_col >= 1) && (k_col <= 39)) && (i_col != k_col_0)) && (delta != ((long )0))) {
              orig[i_col] = orig[i_col] - delta * (C1 / ((orig[k_col_0 + (k_col - k)] + orig[k_col_0 - (39 - k)]) * (orig[i_col + (i - 1)] + orig[i_col - (40 - i)]) + (orig[k_col_0 + (1 + k)] + orig[k_col_0 - (39 - k + 1)])));
            }
          }
        }
      }
    }
  }
}