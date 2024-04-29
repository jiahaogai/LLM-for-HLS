#pragma ACCEL kernel

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
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1 + 0; j <= 392 + 0; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1 + 0; k <= 392 + 0; k++) {
      k_col = 392 - k;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1 + 0; i <= 392 + 0; i++) {
        i_col = 392 - i;
        idx = i + (392 * (k + (392 * j)));
        idx_col = i_col + (392 * (k_col + (392 * j)));
        t = ((((HX(i,k,j) + HX(i_col,k,j)) + HX(i,k_col,j)) + HX(i_col,k_col,j)) - ((((FX(i,k,j) + FX(i_col,k,j)) + FX(i,k_col,j)) + FX(i_col,k_col,j)) * 2));
        sol[idx] = t;
      }
    }
  }
}