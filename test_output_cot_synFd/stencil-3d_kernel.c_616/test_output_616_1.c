#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long idx;
  long idx_col;
  long C0_idx;
  long C1_idx;
  long range_l;
  long range_r;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 2; k < 39302; k++) {...} */
  for (k = 2L; k <= 39301L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 2; j < 39300; j++) {...} */
    for (j = 2L; j <= 39299L; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{30}
      loop_i:
/* Standardize from: for(i = 2; i < 39300; i++) {...} */
      for (i = 2L; i <= 39299L; i++) {
        idx = ((((k - 2) * 39300) + (j - 2)) * 39300) + (i - 2);
        idx_col = ((((39300 - k) * 39300) + (39300 - j)) * 39300) + (39300 - i);
        C0_idx = 0L + C0 * idx;
        C1_idx = C0_idx + C1;
        range_l = idx_col ^ 32767L;
        range_r = (idx_col + 1L) ^ 32767L;
        sol[idx] = ((orig[idx_col] + orig[range_l]) - (orig[range_r])) / ((long )2) + ((orig[C0_idx] + orig[C1_idx]) / ((long )4));
      }
    }
  }
}