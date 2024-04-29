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
  long T0;
  long T1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spx_loop_k:
  for (k = 1; k < 32 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    spx_loop_j:
    for (j = 1; j < 32 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      spx_loop_i:
      for (i = 1; i < 32 + 1; i++) {
        idx = (((32 + 1) * (32 + 1)) * k) + (((32 + 1) * j) + i);
        idx_col = (((32 + 1) * (32 + 1)) * (k - 1)) + (((32 + 1) * (j - 1)) + i);
        T0 = orig[idx_col] + C0 * (orig[idx_col + 1] + orig[idx_col - 1]);
        T1 = orig[idx_col] + C1 * (orig[idx_col + 32] + orig[idx_col - 32]);
        sol[idx] = T0 + T1;
      }
    }
  }
}