#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[128];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k > 32 + 1; k--) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j > 32 + 1; j--) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1; i > 32 + 1; i--) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        buf[0] = orig[i_col + 32L * (j_col + 32L * k_col)];
        buf[1] = orig[i_col + 1L + 32L * (j_col + 32L * k_col)];
        buf[2] = orig[i_col - 1L + 32L * (j_col + 32L * k_col)];
        buf[3] = orig[i_col + 32L * (j_col + 1L + 32L * k_col)];
        buf[4] = orig[i_col + 1L + 32L * (j_col + 1L + 32L * k_col)];
        buf[5] = orig[i_col - 1L + 32L * (j_col + 1L + 32L * k_col)];
        buf[6] = orig[i_col + 32L * (j_col - 1L + 32L * k_col)];
        buf[7] = orig[i_col + 1L + 32L * (j_col - 1L + 32L * k_col)];
        buf[8] = orig[i_col - 1L + 32L * (j_col - 1L + 32L * k_col)];
        sol[i_col + 32L * (j_col + 32L * k_col)] = ((buf[0] + buf[1] + buf[2]) + (buf[3] + buf[4] + buf[5]) + (buf[6] + buf[7] + buf[8])) / 8L;
      }
    }
  }
}