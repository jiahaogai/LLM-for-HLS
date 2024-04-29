#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long idxm1;
  long idxp1;
  long idxm1m1;
  long idxm1p1;
  long idxp1p1;
  long idxp1m1;
  long C0_idx;
  long C1_idx;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j <= 392 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1; k <= 392 - 1; k++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1; i <= 392 - 1; i++) {
        idx = i + (j + (k * 392)) * 393;
        idxm1 = (i - 1) + (j + (k * 392)) * 393;
        idxp1 = (i + 1) + (j + (k * 392)) * 393;
        idxm1m1 = (i - 1) + (j - 1 + (k * 392)) * 393;
        idxm1p1 = (i - 1) + (j + 1 + (k * 392)) * 393;
        idxp1p1 = (i + 1) + (j + 1 + (k * 392)) * 393;
        idxp1m1 = (i + 1) + (j - 1 + (k * 392)) * 393;
        C0_idx = ((k * 4) + 1) * 64;
        C1_idx = ((k * 4 + 2) * 64) + 1;
        tmp = orig[idx] + C0 * (orig[idxm1] + orig[idxp1] + orig[idxm1m1] + orig[idxm1p1] + orig[idxp1p1] + orig[idxp1m1]) + C1 * (sol[idxm1 + C0_idx] + sol[idxp1 + C0_idx] + sol[idxm1p1 + C0_idx] + sol[idxm1m1 + C0_idx] + sol[idxp1p1 + C0_idx] + sol[idxp1m1 + C0_idx]);
        sol[idx + C1_idx] = tmp;
      }
    }
  }
}