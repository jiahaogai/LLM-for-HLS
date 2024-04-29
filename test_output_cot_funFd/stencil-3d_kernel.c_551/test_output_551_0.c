#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long sum;
  long buf[9];
  long C32 = 32L;
  long C16 = 16L;
  long C8 = 8L;
  long C1 = 1L;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k-- > 32 + 1 - 3; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32; j-- > 32 + 1 - 3; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32; i-- > 32 + 1 - 3; ) {
        i_col = i - 1 + ((j - 1) * 32) + ((k - 1) * 32 * 32);
        j_col = j - 1 + (k * 32);
        k_col = k - 1;
        sum = orig[i_col] + orig[j_col] + orig[k_col];
        buf[0] = sum + orig[i_col + C16];
        buf[1] = sum + orig[j_col + C16];
        buf[2] = sum + orig[k_col + C16];
        buf[3] = sum + orig[i_col + C16 + C1];
        buf[4] = sum + orig[j_col + C16 + C1];
        buf[5] = sum + orig[k_col + C16 + C1];
        buf[6] = sum + orig[i_col + C16 + C32];
        buf[7] = sum + orig[j_col + C16 + C32];
        buf[8] = sum + orig[k_col + C16 + C32];
        sol[i_col] = buf[0];
        sol[j_col] = buf[1];
        sol[k_col] = buf[2];
        sol[i_col + C1] = buf[3];
        sol[j_col + C1] = buf[4];
        sol[k_col + C1] = buf[5];
        sol[i_col + C32] = buf[6];
        sol[j_col + C32] = buf[7];
        sol[k_col + C32] = buf[8];
      }
    }
  }
}