#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long k_row;
  long pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1 + 392 * pad;j-- > 1 + 392 * pad; ) {
    long j_col;
    long i_row;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
    for (k_col = 1 + 392 * pad;k_col-- > 1 + 392 * pad; ) {
      i_row = pad + 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_row:
      while (i_row--) {
        j_col = pad + 1;
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loopk_row:
        while (k_col--) {
          i = i_row * 392 + j_col;
          k = pad * 392 + k_row;
          sol[i] = C0 * orig[i] + C1 * (orig[i - 1] + orig[i + 1] + orig[i - 392] + orig[i + 392] + orig[i - 392 * 392] + orig[i + 392 * 392]);
        }
        k_row++;
      }
    }
    k_col = 1 + 392 * pad;
    k_row = pad;
  }
}