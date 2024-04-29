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
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  loop_i:
  for (i = 1; i < 32 + 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    loop_j:
    for (j = 1; j < 32 + 1; j++) {
      loop_k:
      for (k = 1; k < 32 + 1; k++) {
        k_col = ((k - 1) * (32 + 2) * (32 + 2)) + 1;
        j_col = ((j - 1) * (32 + 2)) + 1;
        i_col = ((i - 1) * (32 + 2)) + 1;
        idx = ((k - 1) * (32 + 1) * (32 + 1) + (j - 1) * (32 + 1) + i - 1);
        idx_col = i_col + j_col - 2;
        t = C0 * orig[idx_col] + C1 * (orig[idx_col + 1] + orig[idx_col - 1] + orig[idx_col + 32 - 1] + orig[idx_col - 32 - 1]);
        sol[idx] = t;
      }
    }
  }
}