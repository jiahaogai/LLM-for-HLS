#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{30}

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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj_col:
/* Standardize from: for(j_col = 1;j_col < 40;j_col++) {...} */
  for (j_col = 1; j_col < 40; j_col++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
/* Standardize from: for(k_col = 1;k_col < 40;k_col++) {...} */
    for (k_col = 1; k_col < 40; k_col++) {
      k_col--;
      i_col = 1L;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 40;i_col++) {...} */
      for (; i_col < 40; i_col++) {
        i_col--;
        t = ((C0 * (orig[i_col + ((k_col + 1) * 40) + ((j_col + 1) * 40)] + orig[i_col + ((k_col + 1) * 40) + (j_col * 40)] + orig[i_col + (k_col * 40) + (j_col * 40)]) / 3) + (C1 * (orig[i_col + ((k_col + 2) * 40) + ((j_col + 1) * 40)] + orig[i_col + ((k_col + 2) * 40) + (j_col * 40)] + orig[i_col + (k_col * 40) + (j_col * 40)])));
        sol[i_col + ((k_col + 1) * 40) + ((j_col + 1) * 40)] = t;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj_row:
/* Standardize from: for(j_row = 1;j_row < 40;j_row++) {...} */
  for (j_row = 1; j_row < 40; j_row++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_row:
/* Standardize from: for(k_row = 1;k_row < 40;k_row++) {...} */
    for (k_row = 1; k_row < 40; k_row++) {
      k_row--;
      i_row = 1L;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_row:
/* Standardize from: for(i_row = 1;i_row < 40;i_row++) {...} */
      for (; i_row < 40; i_row++) {
        i_row--;
        idx_col = 1L;
        loopk_idx_col:
/* Standardize from: for(k_col = 0;k_col < 40;k_col++) {...} */
        for (k_col = 0; k_col < 40; k_col++) {
          idx_row = 1L;
          loopj_idx_row:
/* Standardize from: for(j_row = 0;j_row < 40;j_row++) {...} */
          for (j_row = 0; j_row < 40; j_row++) {
            idx_row++;
            idx = idx_col + idx_row - 2L;
            t = orig[i_row + (k_row * 40) + (j_row * 40)];
            sol[i_row + (k_row * 40) + (j_row * 40)] = t * 4L + ((orig[i_row + (k_row * 40) + idx] + orig[i_row + idx + (j_row * 40)]) + orig[i_row + (k_col * 40) + j_row]);
          }
        }
        idx_col++;
      }
    }
  }
}