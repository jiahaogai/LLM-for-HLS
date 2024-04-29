#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j < 392; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
/* Standardize from: for(k_col = 0;k_col < 16;k_col++) {...} */
    for (k_col = 0; k_col < 16; k_col++) {
      i_col = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1; i < 392; i++) {
        idx_col = i + (392 * k_col);
        idx = i + (392 * (k_col + 16 * j));
        t = C0 * (orig[idx_col + 1] - (2 * orig[idx_col]) + orig[idx_col - 1]) + C1 * (orig[idx] - orig[idx_col]);
        sol[idx] = t;
        i_col = i_col + 1;
      }
    }
  }
}