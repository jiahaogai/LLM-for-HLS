#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[27];
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k-- > 32 + 1L; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j-- > 32 + 1L; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i-- > 32 + 1L; ) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        sum = 0L;
        buf[0] = orig[i_col + 32L * (j_col + 32L * k_col)];
        buf[1] = orig[i_col + 1L + 32L * (j_col + 32L * k_col)];
        buf[2] = orig[i_col + 2L + 32L * (j_col + 32L * k_col)];
        buf[3] = orig[i_col + 3L + 32L * (j_col + 32L * k_col)];
        buf[4] = orig[i_col + 4L + 32L * (j_col + 32L * k_col)];
        buf[5] = orig[i_col + 32L * (j_col + 1L + 32L * k_col)];
        buf[6] = orig[i_col + 1L + 32L * (j_col + 1L + 32L * k_col)];
        buf[7] = orig[i_col + 2L + 32L * (j_col + 1L + 32L * k_col)];
        buf[8] = orig[i_col + 3L + 32L * (j_col + 1L + 32L * k_col)];
        buf[9] = orig[i_col + 4L + 32L * (j_col + 1L + 32L * k_col)];
        buf[10] = orig[i_col + 32L * (j_col + 2L + 32L * k_col)];
        buf[11] = orig[i_col + 1L + 32L * (j_col + 2L + 32L * k_col)];
        buf[12] = orig[i_col + 2L + 32L * (j_col + 2L + 32L * k_col)];
        buf[13] = orig[i_col + 3L + 32L * (j_col + 2L + 32L * k_col)];
        buf[14] = orig[i_col + 4L + 32L * (j_col + 2L + 32L * k_col)];
        buf[15] = orig[i_col + 32L * (j_col + 3L + 32L * k_col)];
        buf[16] = orig[i_col + 1L + 32L * (j_col + 3L + 32L * k_col)];
        buf[17] = orig[i_col + 2L + 32L * (j_col + 3L + 32L * k_col)];
        buf[18] = orig[i_col + 3L + 32L * (j_col + 3L + 32L * k_col)];
        buf[19] = orig[i_col + 4L + 32L * (j_col + 3L + 32L * k_col)];
        buf[20] = orig[i_col + 32L * (j_col + 4L + 32L * k_col)];
        buf[21] = orig[i_col + 1L + 32L * (j_col + 4L + 32L * k_col)];
        buf[22] = orig[i_col + 2L + 32L * (j_col + 4L + 32L * k_col)];
        buf[23] = orig[i_col + 3L + 32L * (j_col + 4L + 32L * k_col)];
        buf[24] = orig[i_col + 4L + 32L * (j_col + 4L + 32L * k_col)];
        buf[25] = orig[i_col + 32L * (j_col + 1L + 32L * (k_col + 1L))];
        buf[26] = orig[i_col + 1L + 32L * (j_col + 1L + 32L * (k_col + 1L))];
        loopk_1:
        for (k_col = 0L; k_col < 3L; k_col++) {
          loopj_1:
          for (j_col = 0L; j_col < 3L; j_col++) {
            loopi_1:
            for (i_col = 0L; i_col < 3L; i_col++) {
              sum += buf[i_col + 3L * (j_col + 3L * k_col)] * 32L;
            }
          }
        }
        sol[i + 32L * (j + 32L * k)] = sum;
      }
    }
  }
}