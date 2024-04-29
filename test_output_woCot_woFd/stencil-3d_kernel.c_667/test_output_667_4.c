### Generated Code:
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
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1;j++) {...} */
  for (j = 1; j <= 32; j++) {
    long j_row_start = 32 * (j - 1);
    long j_row_end = 32 * (j - 1) + 31;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{4}
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1;k++) {...} */
    for (k = 1; k <= 32; k++) {
      long k_row_start = 32 * (k - 1);
      long k_row_end = 32 * (k - 1) + 31;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1;i++) {...} */
      for (i = 1; i <= 32; i++) {
        long i_row_start = 32 * (i - 1);
        long i_row_end = 32 * (i - 1) + 31;
        long idx_start = i_row_start * 32 * 32 + j_row_start * 32 + k_row_start;
        long idx_end = i_row_end * 32 * 32 + j_row_end * 32 + k_row_end;
        long idx_col_start = j_row_start * 32 + k_row_start;
        long idx_col_end = j_row_end * 32 + k_row_end;
        long idx_row_start = k_row_start * 32 + i_row_start;
        long idx_row_end = k_row_end * 32 + i_row_end;
//#pragma ACCEL PIPELINE auto{flatten}
//#pragma ACCEL TILE FACTOR=auto{1}
//#pragma ACCEL PARALLEL FACTOR=auto{1}
        loopk_col:
        for (k_col = 1; k_col <= 32; k_col++) {
          loopj_col:
          for (j_col = 1; j_col <= 32; j_col++) {
            loopi_col:
            for (i_col = 1; i_col <= 32; i_col++) {
              idx_col = idx_col_start + (k_col - 1) + (j_col - 1) * 32 + (i_col - 1) * 32 * 32;
              t = orig[idx_col];
            }
          }
        }
//#pragma ACCEL PIPELINE auto{off}
//#pragma ACCEL TILE FACTOR=auto{1}
//#pragma ACCEL PARALLEL FACTOR=auto{2}
        loopk_row:
        for (k_row = 1; k_row <= 32; k_row++) {
          loopj_row:
          for (j_row = 1; j_row <= 32; j_row++) {
            loopi_row:
            for (i_row = 1; i_row <= 32; i_row++) {
              idx_row = idx_row_start + (k_row - 1) + (j_row - 1) * 32 + (i_row - 1) * 32 * 32;
              idx = idx_start + (k_row - 1) + (j_row - 1) * 32 + (i_row - 1) * 32 * 32;
              sol[idx_row] = ((C0 * t) + (C1 * (sol[idx_col - 1] + sol[idx_col + 1] + sol[idx_row - 32] + sol[idx_row + 32] + sol[idx_up - 32 * 32] + sol[idx_up + 32 * 32] + sol[idx_down - 32 * 32] + sol[idx_down + 32 * 32]))) / (C1 + 8);
            }
          }
        }
      }
    }
  }
}