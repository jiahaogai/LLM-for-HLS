#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[27];
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32 - 1; k < 32 + 1 - 1; k++) {
     k_col = 32 * k;
     loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32 - 1; j < 32 + 1 - 1; j++) {
      j_col = 32 * j;
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32 - 1; i < 32 + 1 - 1; i++) {
        i_col = 32 * i;
        sum = ((orig[i_col - 1] + orig[i_col + 1]) + (orig[j_col - 1] + orig[j_col + 1])) + (orig[k_col - 1] + orig[k_col + 1]);
        buf[0] = sum + C0;
        buf[1] = orig[i_col] + C1;
        sol[i_col] = buf[1];
      }
    }
  }
}