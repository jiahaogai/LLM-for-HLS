**TODO:**
 - Complete this stencil function. A complete solution is provided below.

#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[8];
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopk:
/* Standardize from: for(k = 2; k < 3928; k++) {...} */
  for (k = 2 + 3928; k-- > 2 + 0; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 2; j < 3928; j++) {...} */
    for (j = 2 + 3928; j-- > 2 + 0; ) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 2; i < 3928; i++) {...} */
      for (i = 2 + 3928; i-- > 2 + 0; ) {
        i_col = i * C0;
        j_col = j * C1;
        k_col = k * C0;
        sum = 0;
        loopbuf:
        for (long b = 0; b < 8; ++b) {
          long idx = k_col + j_col + i_col + b - 4;
          sum += orig[idx] * buf[b];
        }
        sol[k_col + j_col + i_col] = sum;
      }
    }
  }
}