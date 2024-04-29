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
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_k:
  for (k = 2; k < 392; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 2; j < 392; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
      for (i = 2; i < 392; i++) {
        i_col = i - 2;
        k_col = k - 2;
        idx_col = k_col * 392 + i_col;
        t = C0 * (orig[idx_col] + orig[idx_col + 1]) + C1 * (orig[idx_col + 392] + orig[idx_col + 394]);
        idx = k * 392 + i;
        sol[idx] = t;
      }
    }
  }
}