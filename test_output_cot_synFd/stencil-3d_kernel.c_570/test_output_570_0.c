#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
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
  loopk:
  for (k = 1; k < 32 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
    for (j = 1; j < 32 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 1; i < 32 + 1; i++) {
        i_col = i - 1;
        k_col = k - 1;
        idx_col = k_col * 32 + i_col;
        idx = k * 32 * 32 + j * 32 + i;
        t = orig[idx_col] + orig[idx_col + 1] + orig[idx_col + 32] + orig[idx_col + 33];
        sol[idx] = t;
      }
    }
  }
}