#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long t;
  long pt;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j < 392 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1; k < 392 + 1; k++) {
      pt = k * 392 + j;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1; i < 392 + 1; i++) {
        t = i * 392 + k;
        sol[pt] = ((2 * orig[t]) + (2 * orig[t + 392]) + (2 * orig[t + 392 + 392]) + orig[t + 392 - 1] + orig[t - 1] + orig[t - 392] + orig[t + 392]) / 6.0;
      }
    }
  }
}