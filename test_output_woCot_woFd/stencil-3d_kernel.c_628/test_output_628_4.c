#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[8];
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k-- > 32 + 1L; ) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j-- > 32 + 1L; ) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1; i-- > 32 + 1L; ) {
        i_col = i * 32L;
        j_col = j * 32L;
        k_col = k * 32L;
        buf[0] = orig[i_col + j_col + k_col];
        buf[1] = orig[i_col + j_col + k_col + 1];
        buf[2] = orig[i_col + j_col + k_col + 16];
        buf[3] = orig[i_col + j_col + k_col + 17];
        buf[4] = orig[i_col + j_col + k_col + 32];
        buf[5] = orig[i_col + j_col + k_col + 33];
        buf[6] = orig[i_col + j_col + k_col + 48];
        buf[7] = orig[i_col + j_col + k_col + 49];
        sum = buf[0] + buf[1] + buf[2] + buf[3] + buf[4] + buf[5] + buf[6] + buf[7];
        sol[i_col + j_col + k_col] = sum;
      }
    }
  }
}