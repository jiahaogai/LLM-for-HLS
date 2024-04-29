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
  long k_pad;
  long j_pad;
  long i_pad;
  long idx;
  long idx_col;
  long idx_row;
  long idx_pad;
  long range_pad;
  long range_col;
  long range_row;
  long count;
  long count_col;
  long count_row;
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj_col:
/* Standardize from: for(j_col = 1;j_col < 49;j_col++) {...} */
  for (j_col = 1; j_col < 49 + 1; j_col++) {
    long j_col_tmp = 0 + 49L * (0L + 1L) * (j_col - 1L);
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    loopk_col:
/* Standardize from: for(k_col = 1;k_col < 49;k_col++) {...} */
    for (k_col = 1; k_col < 49 + 1; k_col++) {
      long k_col_tmp = 0 + 49L * (k_col - 1L);
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{3}
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 49;i_col++) {...} */
      for (i_col = 1; i_col < 49 + 1; i_col++) {
        long i_col_tmp = 49L * (i_col - 1L);
        sum = 0L;
        loopj_row:
/* Standardize from: for(j_row = -1;j_row < 2;j_row++) {...} */
        for (j_row = -1; j_row < 2 + 1; j_row++) {
          long j_row_tmp;
          long k_row_tmp;
          if (j_row == -1L) {
            j_row_tmp = -1L;
            k_row_tmp = 49L * (0L + 1L) * (-1L);
          }
          
          if (j_row == 0L) {
            j_row_tmp = 0L;
            k_row_tmp = 49L * (0L + 1L) * (0L);
          }
          
          if (j_row == 1L) {
            j_row_tmp = 1L;
            k_row_tmp = 49L * (0L + 1L) * (1L);
          }
          
          loopk_row:
/* Standardize from: for(k_row = -1;k_row < 2;k_row++) {...} */
          for (k_row = -1; k_row < 2 + 1; k_row++) {
            long k_row_idx = k_row * 49L;
            if (k_row == -1L) {
              k_row_tmp = 49L * (-1L);
            }
            
            if (k_row == 0L) {
              k_row_tmp = 0L;
            }
            
            if (k_row == 1L) {
              k_row_tmp = 49L;
            }
            idx_row = k_row_tmp + j_row_tmp * 49L + i_col_tmp;
            sum += orig[idx_row] << 4;
          }
        }
        idx_col = k_col_tmp + j_col_tmp;
        sol[idx_col] = sum;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj_pad:
/* Standardize from: for(j_pad = 1;j_pad < 49 + 1;j_pad++) {...} */
  for (j_pad = 1; j_pad < 49 + 1; j_pad++) {
    long j_pad_idx = 49L * (j_pad - 1L);
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_pad:
/* Standardize from: for(k_pad = 1;k_pad < 49 + 1;k_pad++) {...} */
    for (k_pad = 1; k_pad < 49 + 1; k_pad++) {
      long k_pad_idx = 49L * (k_pad - 1L);
      idx_pad = k_pad_idx + j_pad_idx;
/* Standardize from: for(i = 0;i < 49;i++) {...} */
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
      for (i = 0; i < 49L; i++) {
        idx = i + 49L * k_pad_idx + j_pad_idx;
        sol[idx_pad] += orig[idx] >> 4;
      }
    }
  }
}