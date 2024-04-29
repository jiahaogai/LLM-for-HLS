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
  spli:
  for (k = 2; k < 32 - 2; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    splj:
    for (j = 2; j < 32 - 2; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      splk:
      for (i = 2; i < 32 - 2; i++) {
        idx = i + (j + (k * 32)) * 32;
        idx_col = i - 2 + (j + (k * 32)) * 32;
        idx_row = i + (j - 2) * 32 + (k * 32);
        idx_in = i + (j + (k * 32)) * 32;
        t = C0 * (orig[idx_in - 1] + orig[idx_in] + orig[idx_in + 1]) + C1 * (orig[idx_col - 32] + orig[idx_col] + orig[idx_col + 32]) + (orig[idx_row - 32] + orig[idx_row] + orig[idx_row + 32]) - orig[idx];
        sol[idx] = t;
      }
    }
  }
}