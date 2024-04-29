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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k-- > 32 + 1L; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j-- > 32 + 1L; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1; i-- > 32 + 1L; ) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        sum = 0L;
        buf[0] = orig[i_col + 32L * (j_col + 32L * k_col)];
        buf[1] = orig[i_col + 1L + 32L * (j_col + 32L * k_col)];
        buf[2] = orig[i_col + 32L * (j_col + 1L + 32L * k_col)];
        buf[3] = orig[i_col + 1L + 32L * (j_col + 1L + 32L * k_col)];
        buf[4] = orig[i_col + 32L * (j_col + 32L + k_col * 32L)];
        buf[5] = orig[i_col + 1L + 32L * (j_col + 32L + k_col * 32L)];
        buf[6] = orig[i_col + 32L * (j_col + 1L + 32L + k_col * 32L)];
        buf[7] = orig[i_col + 1L + 32L * (j_col + 1L + 32L + k_col * 32L)];
        buf[8] = orig[i_col + 32L * (j_col + 32L + (k_col + 1L) * 32L)];
        buf[9] = orig[i_col + 1L + 32L * (j_col + 32L + (k_col + 1L) * 32L)];
        buf[10] = orig[i_col + 32L * (j_col + 1L + 32L + (k_col + 1L) * 32L)];
        buf[11] = orig[i_col + 1L + 32L * (j_col + 1L + 32L + (k_col + 1L) * 32L)];
        buf[12] = orig[i_col + ((j_col + 32L) % 32L) * 32L + ((k_col + 32L) % 32L) * 1024L];
        buf[13] = orig[i_col + 1L + ((j_col + 32L) % 32L) * 32L + ((k_col + 32L) % 32L) * 1024L];
        buf[14] = orig[i_col + ((j_col + 1L + 32L) % 32L) * 32L + ((k_col + 32L) % 32L) * 1024L];
        buf[15] = orig[i_col + 1L + ((j_col + 1L + 32L) % 32L) * 32L + ((k_col + 32L) % 32L) * 1024L];
        buf[16] = orig[i_col + ((j_col + 32L) % 32L) * 32L + ((k_col + 1L) % 32L) * 1024L];
        buf[17] = orig[i_col + 1L + ((j_col + 32L) % 32L) * 32L + ((k_col + 1L) % 32L) * 1024L];
        buf[18] = orig[i_col + ((j_col + 1L + 32L) % 32L) * 32L + ((k_col + 1L) % 32L) * 1024L];
        buf[19] = orig[i_col + 1L + ((j_col + 1L + 32L) % 32L) * 32L + ((k_col + 1L) % 32L) * 1024L];
        buf[20] = orig[i_col + ((j_col + 32L) % 32L) * 32L + ((k_col + 32L) % 32L) * 1024L];
        buf[21] = orig[i_col + 1L + ((j_col + 32L) % 32L) * 32L + ((k_col + 32L) % 32L) * 1024L];
        buf[22] = orig[i_col + ((j_col + 1L + 32L) % 32L) * 32L + ((k_col + 32L) % 32L) * 1024L];
        buf[23] = orig[i_col + 1L + ((j_col + 1L + 32L) % 32L) * 32L + ((k_col + 32L) % 32L) * 1024L];
        buf[24] = orig[i_col + ((j_col + 32L) % 32L) * 32L + ((k_col + 1L) % 32L) * 1024L];
        buf[25] = orig[i_col + 1L + ((j_col + 32L) % 32L) * 32L + ((k_col + 1L) % 32L) * 1024L];
        buf[26] = orig[i_col + ((j_col + 1L + 32L) % 32L) * 32L + ((k_col + 1L) % 32L) * 1024L];
        sum += buf[0] - C0;
        sum += buf[1] - C0;
        sum += buf[2] - C0;
        sum += buf[3] - C0;
        sum += buf[4] - C0;
        sum += buf[5] - C0;
        sum += buf[6] - C0;
        sum += buf[7] - C0;
        sum += buf[8] - C0;
        sum += buf[9] - C0;
        sum += buf[10] - C0;
        sum += buf[11] - C0;
        sum += buf[12] - C0;
        sum += buf[13] - C0;
        sum += buf[14] - C0;
        sum += buf[15] - C0;
        sum += buf[16] - C0;
        sum += buf[17] - C0;
        sum += buf[18] - C0;
        sum += buf[19] - C0;
        sum += buf[20] - C0;
        sum += buf[21] - C0;
        sum += buf[22] - C0;
        sum += buf[23] - C0;
        sum += buf[24] - C0;
        sum += buf[25] - C0;
        sum += buf[26] - C0;
        sol[i + 32L * (j + 32L * k)] = sum;
      }
    }
  }
}