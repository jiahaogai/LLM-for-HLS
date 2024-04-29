#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long k_row;
  long i_row;
  long idx;
  long idx_col;
  long idx_row;
  long idx_in;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  sp_loop:
  for (k = 2; k < 32 + 2; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    sp_loopj:
    for (j = 2; j < 32 + 2; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      sp_loopi:
      for (i = 2; i < 32 + 2; i++) {
        idx = (((32 + 2) * 32) * (k - 2)) + (((32 + 2) * 16) * (j - 2)) + ((32 + 2) * (i - 2));
        idx_col = (((32 + 2) * 32) * (k - 1)) + (((32 + 2) * 16) * (j - 2)) + ((32 + 2) * (i - 2));
        idx_row = (((32 + 2) * 32) * (k - 2)) + (((32 + 2) * 16) * (j - 1)) + ((32 + 2) * (i - 2));
        idx_in = (((32 + 2) * 32) * (k - 2)) + (((32 + 2) * 16) * (j - 2)) + ((32 + 2) * (i - 1));
        t = C0 * (orig[idx_in] - ((orig[idx_col] + orig[idx_row]) / 2.0));
        sol[idx] = orig[idx] + t;
      }
    }
  }
}