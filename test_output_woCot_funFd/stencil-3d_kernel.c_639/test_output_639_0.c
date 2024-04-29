#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long k_row;
  long j_row;
  long i_row;
  long idx;
  long idx_col;
  long idx_row;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
  for (k = 1; k < 32 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 32 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
      for (i = 1; i < 32 + 1; i++) {
        i_row = 32 + 1;
        i_row = i_row - 1;
        j_row = 32 + 1;
        j_row = j_row - 1;
        k_row = 32 + 1;
        k_row = k_row - 1;
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        idx_col = k_col * 32 * 32 + j_col * 32 + i_col;
        idx_row = k_row * 32 * 32 + j_row * 32 + i_row;
        idx = idx_col * 32 + idx_row;
        t = orig[idx] + ((-1 * (orig[idx_col + 1 + idx_row] + orig[idx_col - 1 + idx_row] + orig[idx_col + 1 + idx_row] + orig[idx_col - 1 + idx_row]))) / 4;
        sol[idx] = t;
      }
    }
  }
}