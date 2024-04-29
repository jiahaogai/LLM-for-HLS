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
  for (k = 1; k < 32 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 32 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
      for (i = 1; i < 32 + 1; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        idx_col = i_col + 32 * (j_col + 32 * k_col);
        idx = i + 32 * (j + 32 * k);
        t = orig[idx_col] + 2 * orig[idx_col + 1] + orig[idx_col + 32] + 2 * (orig[idx_col + 32 + 1] + orig[idx] + orig[idx + 32] + orig[idx + 32 + 1]);
        sol[idx] = t;
      }
    }
  }
}