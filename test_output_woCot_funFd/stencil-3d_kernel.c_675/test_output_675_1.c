#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopk_col:
/* Standardize from: for(k_col = 1;k_col < 40;k_col++) {...} */
  for (k_col = 1; k_col < 40 + 1L; k_col++) {
    long k_col_tmp = 40L + 1L - k_col;
    long pad = k_col_tmp;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj_col:
/* Standardize from: for(j_col = 1;j_col < 40;j_col++) {...} */
    for (j_col = 1; j_col < 40 + 1L; j_col++) {
      long j_col_tmp = 40L + 1L - j_col;
      long pad = j_col_tmp;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 40;i_col++) {...} */
      for (i_col = 1; i_col < 40 + 1L; i_col++) {
        long i_col_tmp = 40L + 1L - i_col;
        long pad = i_col_tmp;
        i = 0 + pad;
        j = 0 + pad;
        k = 0 + pad;
        buf = 0L;
        loopk:
#pragma ACCEL PARALLEL FACTOR=auto{8}
        for (; k < 40L; k++) {
          j = 0L;
          loopj:
#pragma ACCEL PARALLEL FACTOR=auto{8}
          for (; j < 40L; j++) {
            i = 0L;
            loopi:
#pragma ACCEL PARALLEL FACTOR=auto{8}
            for (; i < 40L; i++) {
              buf += orig[i + 1 + (j + 1) * 40 + (k + 1) * 40 * 40] * 4.0;
            }
          }
        }
        sol[pad] = buf;
      }
    }
  }
}