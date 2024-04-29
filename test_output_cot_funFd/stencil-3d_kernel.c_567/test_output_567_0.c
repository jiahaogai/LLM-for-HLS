#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long k_row;
  long tmp;
  long C0_FIXED = C0;
  long C1_FIXED = C1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 1;j++) {...} */
  for (j = 1 + 1; j < 32 + 1 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{4}
    loopk_col:
/* Standardize from: for(k_col = 1;k_col < 32 + 1 - 1;k_col++) {...} */
    for (k_col = 1 + 1; k_col < 32 + 1 - 1; k_col++) {
      loopk_row:
/* Standardize from: for(k_row = 0;k_row < 32 + 1;k_row++) {...} */
      for (k_row = 0; k_row < 32 + 1; k_row++) {
        long k_ind = ((((k_row * (32L + 1L)) + k_col) * (39L)) + 1L);
        tmp = ((((C0_FIXED * (orig[k_ind - 1 - 32L - 1L] + orig[k_ind - 32L - 1L] + orig[k_ind + 1 - 32L - 1L] + orig[k_ind - 1] + orig[k_ind + 1] + orig[k_ind - 1 + 32L] + orig[k_ind + 32L] + orig[k_ind + 1 + 32L])) / C1_FIXED) + orig[k_ind]) / 2L;
        sol[k_ind] = tmp;
      }
    }
  }
}