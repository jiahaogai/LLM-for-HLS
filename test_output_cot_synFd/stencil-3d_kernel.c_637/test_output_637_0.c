**TODO:**
 - C0 = 40
 - C1 = 40

#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 1;j < 40 - 1;j++) {...} */
  for (j = 1 + 0; j <= 40 - 1 + 0; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 40 - 1;k++) {...} */
    for (k = 1 + 0; k <= 40 - 1 + 0; k++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 40 - 1;i++) {...} */
      for (i = 1 + 0; i <= 40 - 1 + 0; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        buf = orig[i_col + 40L * (j_col + 40L * k_col)] + 40L * 40L * 40L / 2L;
        sol[i_col + 40L * (j_col + 40L * k_col)] = buf;
      }
    }
  }
}