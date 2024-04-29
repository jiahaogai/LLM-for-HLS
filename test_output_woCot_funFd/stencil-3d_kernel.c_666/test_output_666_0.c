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
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k > 32 + 1; k--) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32; j > 32 + 1; j--) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32; i > 32 + 1; i--) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        sum = ((long )0);
        loop_buf:
/* Standardize from: for(idx_buf = 0; idx_buf < 27; ++idx_buf) {...} */
        for (idx_buf = 0; idx_buf < 27; idx_buf++) {
          buf[idx_buf] = orig[i_col + ((j_col + ((k_col + idx_buf) * 32)) * 32)];
          sum += buf[idx_buf];
        }
        sol[i_col + ((j_col + (k_col * 32)) * 32)] = sum;
      }
    }
  }
}