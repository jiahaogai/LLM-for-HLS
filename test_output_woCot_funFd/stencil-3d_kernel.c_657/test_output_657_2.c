#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long pass;
  long j_col;
  long k_row;
  long i_row;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j < 392 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1; k < 392 + 1; k++) {
      k_col = ((392 + 2) * (k - 1)) + 1;
      i_col = ((392 + 2) * (j - 1)) + 1;
      pass = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 1; i < 392 + 1; i++) {
        idx_col = k_col + i;
        t = orig[idx_col] + ((C0 * (orig[i_col + 1] + orig[i_col - 1])) + (C1 * (orig[k_col + 1] + orig[k_col - 1])));
        if (t < 0) {
          t = 0;
        }
        if (t > 4095) {
          t = 4095;
        }
        sol[idx_col] = t;
        i_col = i_col + 1;
      }
      k_row = ((392 + 2) * (k - 1)) + 1;
      i_row = ((392 + 2) * (j - 1)) + 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopjj:
      for (jj = 1; jj < 392 + 1; jj++) {
        idx = i_row + jj;
        if (sol[idx] > 4095) {
          sol[idx] = 4095;
        }
        else if (sol[idx] < 0) {
          sol[idx] = 0;
        }
      }
    }
    if (pass == 1) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopjj:
      for (jj = 1; jj < 392 + 1; jj++) {
        idx = i_row + jj;
        sol[idx] = ((4096 * sol[idx]) + 8192) >> 12;
      }
    }
  }
}