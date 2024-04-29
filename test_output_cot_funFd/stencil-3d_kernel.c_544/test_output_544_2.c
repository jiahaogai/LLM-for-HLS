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
  long tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j < 392 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1; k < 392 + 1; k++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1; i < 392 + 1; i++) {
        idx = i + (j + (k * 392)) * 392;
        idxm1 = (i - 1) + (j + (k * 392)) * 392;
        idxp1 = (i + 1) + (j + (k * 392)) * 392;
        idxm1m1 = (i - 1) + (j - 1 + (k * 392)) * 392;
        idxm1p1 = (i - 1) + (j + 1 + (k * 392)) * 392;
        idxp1p1 = (i + 1) + (j + 1 + (k * 392)) * 392;
        tmp = orig[idx] + ((C0 * (orig[idxm1] + orig[idxp1])) / (2 * 392) + (C1 * (orig[idxm1m1] + orig[idxm1p1] + orig[idxp1p1])) / (2 * 8)) / (2 * 392);
        sol[idx] = tmp;
      }
    }
  }
}