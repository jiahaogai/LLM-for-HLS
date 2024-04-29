#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long C0_idx;
  long C1_idx;
  long range_l;
  long range_r;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (range_l = 1, range_r = 40; range_l < range_r; range_l++, range_r--) {
    k = range_r;
    k_col = k - 1;
    idx_col = k_col * 80;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 80; j++) {...} */
    for (range_l = 1, range_r = 80; range_l < range_r; range_l++, range_r--) {
      j = range_r;
      i_col = j - 1;
      idx = idx_col + i_col;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (range_l = 1, range_r = 40; range_l < range_r; range_l++, range_r--) {
        i = range_r;
        C0_idx = i * 40 + j;
        C1_idx = j * 40 + i;
        sol[idx] = C0 * orig[C0_idx] + C1 * orig[C1_idx];
      }
    }
  }
}