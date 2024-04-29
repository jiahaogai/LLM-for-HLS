#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long k_col;
  long j_col;
  long i_col;
  long upper_bound;
  long lower_bound;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_i:
  for (i = 1; i < 32 + 1; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 32 + 1; j++) {
      loop_k:
      for (k = 1; k < 32 + 1; k++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        upper_bound = (i_col > 32 - 1 ? 32 - 1 : i_col);
        lower_bound = (i_col < 0 ? 0 : i_col);
        idx = ((k_col * (32L + 2L) + j_col) * (32L + 2L) + lower_bound) + 1;
        t = orig[idx] + ((C0 * (orig[idx + 1] + orig[idx - 1])) + (C1 * (orig[idx + (32L + 2L)] + orig[idx - (32L + 2L)])));
        sol[idx] = t;
      }
    }
  }
}