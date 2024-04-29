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
  long buf[256];
  long tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 2;j++) {...} */
  for (j = 1 + 32L; j-- > 32 + 1 - 2; ) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 2;k++) {...} */
    for (k = 1 + 32L; k-- > 32 + 1 - 2; ) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 2;i++) {...} */
      for (i = 1 + 32L; i-- > 32 + 1 - 2; ) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        tmp = orig[i_col + (j_col + (k_col + 39304L * (32L + 1L - 2L) << 1L))];
        buf[0] = tmp;
        buf[1] = orig[i_col + (j_col + (k_col + 39304L * (32L + 1L - 2L)) << 1L)];
        buf[2] = orig[i_col + (j_col + (k_col + 39304L * (32L + 1L - 2L) << 1L) + 39304L)];
        buf[3] = orig[i_col + (j_col + (k_col + 39304L * (32L + 1L - 2L) << 1L) + (39304L << 1L))];
        buf[4] = orig[i_col + (j_col + (k_col + 39304L * (32L + 1L - 2L) << 2L))];
        buf[5] = orig[i_col + (j_col + (k_col + 39304L * (32L + 1L - 2L) << 2L) + 39304L)];
        buf[6] = orig[i_col + (j_col + (k_col + 39304L * (32L + 1L - 2L) << 2L) + (39304L << 1L))];
        buf[7] = orig[i_col + (j_col + (k_col + 39304L * (32L + 1L - 2L) << 2L) + (39304L << 2L))];
        sol[i + (j + (k + 32L * (32L + 1L - 2L) << 1L)) - 1] = ((buf[-1] + buf[8]) + ((buf[0] + buf[7]) - (buf[1] + buf[6]))) + ((buf[2] + buf[5]) - (buf[3] + buf[4]));
      }
    }
  }
}