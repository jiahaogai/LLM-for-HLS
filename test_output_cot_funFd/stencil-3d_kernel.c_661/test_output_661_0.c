#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loop_k:
  for (k = 1; k < 32 + 1 - 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 32 + 1 - 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_i:
      for (i = 1; i < 32 + 1 - 1; i++) {
        idx = (((32 + 1 - 1) * (32 + 1 - 1)) * k) + (((32 + 1 - 1) * j) + i);
        idx_col = (((32 + 1 - 1) * (32 + 1 - 1)) * (k - 1)) + (((32 + 1 - 1) * (j - 1)) + i);
        t = orig[idx_col] + 0.5 * (orig[idx_col + 1] - orig[idx_col - 1]) + 0.5 * (orig[idx_col + 32 + 1 - 1] - orig[idx_col - 32 + 1 - 1]) + 0.5 * (orig[idx_col + 32 * (32 + 1 - 1)] - orig[idx_col - 32 * (32 + 1 - 1)]);
        sol[idx] = ((1.0 / 4.0) * t);
      }
    }
  }
}