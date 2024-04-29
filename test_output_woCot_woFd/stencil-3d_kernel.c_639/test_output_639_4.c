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
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
  for (k = 0; k < 40; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 0; j < 40; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
      for (i = 0; i < 40; i++) {
        i_col = i - 1;
        if (i == 0) {
          i_col = i;
        }
        j_col = j - 1;
        if (j == 0) {
          j_col = j;
        }
        k_col = k - 1;
        if (k == 0) {
          k_col = k;
        }
        idx = i + (40 * j) + (40 * 40 * k);
        idx_col = i_col + (40 * j_col) + (40 * 40 * k_col);
        t = orig[idx_col] + 2 * orig[idx] + orig[idx + 40] + 2 * (orig[idx + 40 * 40] + orig[idx_col + 40 * 40]);
        sol[idx] = t;
      }
    }
  }
}