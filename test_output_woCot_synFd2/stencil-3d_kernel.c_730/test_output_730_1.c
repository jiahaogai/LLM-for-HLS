#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long ko;
  long ki;
  long kj;
  long i_col;
  long j_col;
  long k_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1; j < 32 + 1; j++) {...} */
  for (j = 1; j <= 32; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1; k < 32 + 1; k++) {...} */
    for (k = 1; k <= 32; k++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1; i++) {...} */
      for (i = 1; i <= 32; i++) {
         i_col = -1 * (32 - i);
         j_col = -1 * (32 - j);
         k_col = -1 * (32 - k);
         idx = i + (32 * (j + (32 * k)));
         idx_col = i_col + (32 * (j_col + (32 * k_col)));
         t = (((C0 * (orig[idx] - orig[idx_col])) + (C1 * (orig[idx + 1] - orig[idx_col + 1]))) + orig[idx]) >> 15;
         sol[idx] = t;
      }
    }
  }
}