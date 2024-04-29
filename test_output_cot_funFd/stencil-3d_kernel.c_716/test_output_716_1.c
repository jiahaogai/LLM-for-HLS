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
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k-- > 32 + 1; ) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j-- > 32 + 1 - 2; ) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 3; i-- > 32 + 1 - 3; ) {
        i_col = i - 1 + ((j - 1) * 32) + ((k - 1) * 32 * 32);
        j_col = j - 1 + (k * 32);
        k_col = k - 1;
        sum = 0;
        buf[0] = orig[i_col - 32 - 1];
        buf[1] = orig[i_col - 32];
        buf[2] = orig[i_col - 32 + 1];
        buf[3] = orig[i_col - 1];
        buf[4] = orig[i_col];
        buf[5] = orig[i_col + 1];
        buf[6] = orig[i_col + 32 - 1];
        buf[7] = orig[i_col + 32];
        buf[8] = orig[i_col + 32 + 1];
        loopbuf:
#pragma ACCEL PARALLEL FACTOR=auto{3}
        for (long buf_idx = 0; buf_idx < 9; ++buf_idx) {
          sum += buf[buf_idx];
        }
        sol[i_col] = sum;
      }
    }
  }
}