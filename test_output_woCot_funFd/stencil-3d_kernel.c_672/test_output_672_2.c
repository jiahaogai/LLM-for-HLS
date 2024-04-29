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
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopk_col:
/* Standardize from: for(k_col = 1;k_col < 40;k_col ++) {...} */
  for (k_col = 1; k_col < 40 + 1L; k_col ++) {
     long k_col_tmp = 40L + 1L - k_col;
     long pad = k_col_tmp;
     long pad2 = pad << 1;
     long pad3x2 = (pad2 + 2) << 1;
    loopj_col:
/* Standardize from: for(j_col = 1;j_col < 40;j_col ++) {...} */
    for (j_col = 1; j_col < 40 + 1L; j_col ++) {
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 40;i_col ++) {...} */
      for (i_col = 1; i_col < 40 + 1L; i_col ++) {
        buf = orig[i_col + pad3x2 + (j_col + pad) * 39 + (k_col + pad) * 39 * 40];
        sol[i_col + j_col * 40 + k_col * 40 * 40] = buf;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1;k < 40 - 2;k ++) {...} */
  for (k = 1; k < 40 - 2L; k ++) {
     long k_tmp = k;
     long pad = 40L;
     long pad2 = pad << 1;
     long pad3 = pad2 + 1;
     long pad3x2 = (pad2 + 2) << 1;
    loopj:
/* Standardize from: for(j = 1;j < 40 - 2;j ++) {...} */
    for (j = 1; j < 40 - 2L; j ++) {
      long j_tmp = j;
      long col = k_tmp * 39 * 40 + j_tmp * 40 + pad3x2;
       loopi:
/* Standardize from: for(i = 1;i < 40 - 2;i ++) {...} */
      for (i = 1; i < 40 - 2L; i ++) {
        long i_tmp = i;
        long sum = 0L;
        long local_buf = orig[col + i_tmp];
        sum += local_buf;
        local_buf = orig[col + i_tmp + 1L];
        sum += local_buf;
        local_buf = orig[col + i_tmp + 1L + 1L];
        sum += local_buf;
        local_buf = orig[col + i_tmp + 2L];
        sum += local_buf;
        sol[col + i_tmp] = sum;
      }
    }
  }
}