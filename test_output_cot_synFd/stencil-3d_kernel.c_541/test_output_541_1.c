#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{4}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
  long tmp;
  long tmp_row;
  long tmp_col;
  long tmp_inner;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk_col:
/* Standardize from: for(k_col = 1;k_col < 40;k_col++) {...} */
  for (k_col = 1; k_col < 40; k_col++) {
    long k_col_idx_start = (k_col - 1) * 80 * 40;
    long k_col_idx_end = k_col_idx_start + 80 * 40 - 1;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj_col:
/* Standardize from: for(j_col = 1;j_col < 80;j_col++) {...} */
    for (j_col = 1; j_col < 80; j_col++) {
      long j_col_idx_start = (j_col - 1) * 40 + k_col_idx_start;
      long j_col_idx_end = j_col_idx_start + 40 - 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 40;i_col++) {...} */
      for (i_col = 1; i_col < 40; i_col++) {
        long i_col_idx = i_col + j_col_idx_start;
        tmp = orig[i_col_idx];
        buf = tmp * 4 + orig[i_col_idx + 40] + orig[i_col_idx + 1] * 2;
        tmp_col = buf * 2 + orig[i_col_idx + 1 + 40];
        buf = tmp_col * 4 + orig[i_col_idx - 1] + orig[i_col_idx + 40 - 1];
        tmp_row = buf * 2 + orig[i_col_idx + 40 - 1];
        buf = tmp_row * 4 + orig[i_col_idx - 1 - 40] + orig[i_col_idx - 1];
        tmp_inner = buf * 2 + orig[i_col_idx - 1 - 40];
        sol[i_col_idx] = tmp_inner;
      }
    }
  }
}