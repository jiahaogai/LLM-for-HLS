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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 8; k++) {...} */
  for (k = 8L; k < 32L + 1L - 8L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 8; j++) {...} */
    for (j = 8L; j < 32L + 1L - 8L; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 8; i++) {...} */
      for (i = 8L; i < 32L + 1L - 8L; i++) {
        i_col = i - 8L;
        j_col = j - 8L;
        k_col = k - 8L;
        sum = ((C0 * (orig[k_col * 32L * 32L + j_col * 32L + i_col] + orig[k_col * 32L * 32L + j_col * 32L + i_col + 1L] ) + C1 * (orig[k_col * 32L * 32L + j_col * 32L + i_col + 32L ] + orig[k_col * 32L * 32L + j_col * 32L + i_col + 33L ] ) ) + ((C0 + C1) * (orig[k_col * 32L * 32L + j_col * 32L + i_col + 16L ] + orig[k_col * 32L * 32L + j_col * 32L + i_col + 48L ] ))) / (C0 + C1 + 2.0);
        buf[0] = sum;
        buf[1] = orig[k_col * 32L * 32L + j_col * 32L + i_col + 2L];
        buf[2] = orig[k_col * 32L * 32L + j_col * 32L + i_col + 3L];
        buf[3] = orig[k_col * 32L * 32L + j_col * 32L + i_col + 4L];
        buf[4] = sum + buf[2];
        buf[5] = buf[1] + buf[4];
        buf[6] = orig[k_col * 32L * 32L + j_col * 32L + i_col + 5L];
        buf[7] = buf[3] + buf[6];
        buf[8] = buf[5] + buf[7];
        sol[k_col * 32L * 32L + j_col * 32L + i_col] = buf[8];
      }
    }
  }
}