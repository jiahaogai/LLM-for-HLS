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
  long idx_in;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 3;j++) {...} */
  for (j = 1 + 32 - 1; j < 32 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
    for (k = 1 + 32 - 1; k < 32 + 1; k++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1;i++) {...} */
      for (i = 1; i < 32 + 1 - 1; i++) {
         k_col = ((32 + 1) * (32 + 1)) * k;
         i_col = (32 + 1) * i;
        loopj_col:
/* Standardize from: for(j_col = 0;j_col < 32 + 1;j_col++) {...} */
        for (j_col = 0; j_col < 32 + 1; j_col++) {
          idx_col = k_col + i_col + j_col;
          t = orig[idx_col] + C0 * ((((32 + 1) * (2)) * k) + ((32 + 1) * j) + i);
        }
      }
      k_row = ((32 + 1) * (31 + 1)) * k;
      i_row = (32 + 1) * i;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopj_row:
/* Standardize from: for(j_row = 1;j_row < 32 + 1 - 1;j_row++) {...} */
      for (j_row = 1; j_row < 32 + 1 - 1; j_row++) {
        idx_row = k_row + i_row + j_row;
        loopi_row:
/* Standardize from: for(i_row = 0;i_row < 32 + 1;i_row++) {...} */
        for (i_row = 0; i_row < 32 + 1; i_row++) {
          idx_in = idx_row - (32 + 1) * j_row + i_row;
          sol[idx_in] = t;
        }
      }
    }
  }
}