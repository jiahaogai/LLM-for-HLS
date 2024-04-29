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
  long k_up;
  long i_up;
  long j_up;
  long k_down;
  long i_down;
  long j_down;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k > 32 + 1; k--) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopj:
    for (j = 1 + 32; j > 32 + 1; j--) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
      for (i = 1 + 32; i > 32 + 1; i--) {
        k_col = ((k - 1) * 32) + 1;
        i_col = ((i - 1) * 32) + 1;
        j_col = ((j - 1) * 32) + 1;
        k_row = ((k + 0) * 32) + 1;
        i_row = ((i + 0) * 32) + 1;
        j_row = ((j + 0) * 32) + 1;
        k_up = ((k - 1) * 32) + 0;
        i_up = ((i - 1) * 32) + 0;
        j_up = ((j - 1) * 32) + 0;
        k_down = ((k + 1) * 32) + 0;
        i_down = ((i + 1) * 32) + 0;
        j_down = ((j + 1) * 32) + 0;
        tmp = orig[k_col + i_col + j_col] + C0 * (orig[k_row + i_col + j_col] + orig[k_up + i_col + j_col] + orig[k_down + i_col + j_col] + orig[k_col + i_row + j_col] + orig[k_col + i_up + j_col] + orig[k_col + i_down + j_col] + orig[k_col + i_col + j_row] + orig[k_col + i_col + j_up] + orig[k_col + i_col + j_down]);
        sol[k_col + i_col + j_col] = tmp;
      }
    }
  }
}