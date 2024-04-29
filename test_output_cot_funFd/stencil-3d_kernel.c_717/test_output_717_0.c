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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j < 392 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1; k < 392 + 1; k++) {
      idx = ((392 + 2) * (392 + 2)) * j + (392 + 2) * k + 1;
      idxm1 = ((392 + 2) * (392 + 2)) * j + (392 + 2) * (k - 1) + 1;
      idxp1 = ((392 + 2) * (392 + 2)) * j + (392 + 2) * (k + 1) + 1;
      idxm1m1 = ((392 + 2) * (392 + 2)) * (j - 1) + (392 + 2) * (k - 1) + 1;
      idxm1p1 = ((392 + 2) * (392 + 2)) * (j - 1) + (392 + 2) * (k + 1) + 1;
      idxp1p1 = ((392 + 2) * (392 + 2)) * (j + 1) + (392 + 2) * (k + 1) + 1;
      tmp = C0 * (orig[idxm1m1] + orig[idxm1p1] + orig[idxp1p1] - orig[idxm1p1] - orig[idxp1m1] - orig[idxp1p1]);
      sol[idx] = tmp + ((C1 - 1.0) * orig[idx]);
    }
  }
}