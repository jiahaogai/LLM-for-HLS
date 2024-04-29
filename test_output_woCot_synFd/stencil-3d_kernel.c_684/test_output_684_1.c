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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 2; k++) {...} */
  for (k = 1 + 32L; k-- > 32 + 1L; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j-- > 32 + 1L; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 2; i++) {...} */
      for (i = 1 + 32L; i-- > 32 + 1L; ) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        buf[0] = orig[i_col + 32L * (j_col + 32L * k_col)];
        buf[1] = orig[i_col + 1L + 32L * (j_col + 32L * k_col)];
        buf[2] = orig[i_col + 32L * (j_col + 1L + 32L * k_col)];
        buf[3] = orig[i_col + 1L + 32L * (j_col + 1L + 32L * k_col)];
        buf[4] = orig[i_col + 32L * (j_col + 32L + k_col * 32L)];
        buf[5] = orig[i_col + 1L + 32L * (j_col + 32L + k_col * 32L)];
        buf[6] = orig[i_col + 32L * (j_col + 1L + 32L + k_col * 32L)];
        buf[7] = orig[i_col + 1L + 32L * (j_col + 1L + 32L + k_col * 32L)];
        sol[i_col + 32L * (j_col + 32L * k_col)] = ((C0 * buf[0]) + (C1 * buf[1]) + (C0 * buf[2]) + (C1 * buf[3]) + (C0 * buf[4]) + (C1 * buf[5]) + (C0 * buf[6]) + (C1 * buf[7])) / 256L;
      }
    }
  }
}