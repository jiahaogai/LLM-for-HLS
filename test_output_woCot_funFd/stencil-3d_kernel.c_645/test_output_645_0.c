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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  sp:
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    sm:
    for (j = 0; j < 40; j++) {
      s:
      for (k = 0; k < 40; k++) {
        idx = i * 40 * 40 + j * 40 + k;
        k_col = (k + 40 - 1) % 40;
        i_col = (i + 40 - 1) % 40;
        idx_col = i_col * 40 * 40 + j * 40 + k_col;
        t = C0 * orig[idx_col] + C1 * (orig[idx_col + 1] + orig[idx_col - 1] + orig[idx_col + 40] + orig[idx_col - 40] + orig[idx_col + 40 * 40] + orig[idx_col - 40 * 40]);
        sol[idx] = t;
      }
    }
  }
}