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
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_i:
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 0; j < 40; j++) {
      loop_k:
      for (k = 0; k < 40; k++) {
        k_col = ((40 + 2) * k) - 2;
        j_col = ((40 + 2) * j) - 2;
        i_col = ((40 + 2) * i) - 2;
        idx = (k_col * 40) + j_col;
        idx_col = (i_col * 40) + k_col;
        t = ((((orig[idx_col + 1] + orig[idx_col + 2]) + orig[idx_col + 3]) + orig[idx_col + 4]) + orig[idx_col + 5]) + orig[idx_col + 6] - ((((orig[idx_col - 1] + orig[idx_col + 0]) + orig[idx_col + 1]) + orig[idx_col + 2]) + orig[idx_col + 3]) - ((((orig[idx - 40] + orig[idx - 32]) + orig[idx - 24]) + orig[idx - 16]) + orig[idx - 8]) - orig[idx];
        sol[idx] = t;
      }
    }
  }
}