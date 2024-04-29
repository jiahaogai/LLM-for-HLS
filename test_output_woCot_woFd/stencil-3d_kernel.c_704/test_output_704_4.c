#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long k_row;
  long i_row;
  long j_row;
  long idx;
  long idx_col;
  long idx_row;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 40; j++) {
      inner:
      for (k = 0; k < 40; k++) {
        i_col = (i - 1 + 40) % 40;
        j_col = (j - 1 + 40) % 40;
        k_col = (k - 1 + 40) % 40;
        i_row = (i + 1) % 40;
        j_row = (j + 1) % 40;
        k_row = (k + 1) % 40;
        idx_col = i_col * 40 + j_col * 4;
        idx_row = i_row * 40 + j_row * 4;
        idx = i * 40 + j * 4 + k;
        t = C0 * orig[idx] + C1 * (orig[idx_col + k_col] + orig[idx_row + k_row]);
        sol[idx] = t;
      }
    }
  }
}