#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304][32768],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 32768 - 1;j++) {...} */
  for (j = 1; j <= 32768 - 2; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 39304 - 1;k++) {...} */
    for (k = 1; k <= 39304 - 2; k++) {
      s = 0;
      loopi:
/* Standardize from: for(i = 1;i < 39304;i++) {...} */
      for (i = 1; i <= 39304 - 1; i++) {
        idx = i * 32768 + j * 39304 + k;
        s += orig[i - 1][j][k] + orig[i + 1][j][k] + orig[i][j - 1][k] + orig[i][j + 1][k] + orig[i][j][k - 1] + orig[i][j][k + 1] - 6 * orig[i][j][k];
      }
      sol[idx] = s;
    }
  }
}