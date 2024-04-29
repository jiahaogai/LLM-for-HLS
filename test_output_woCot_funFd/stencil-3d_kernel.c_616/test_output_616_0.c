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
  loop_j:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j < 392 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_k:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1; k < 392 + 1; k++) {
      idx = (j - 1) * 392 + k - 1;
      idxm1 = idx - 1;
      idxp1 = idx + 1;
      idxm1m1 = idxm1 - 1;
      idxm1p1 = idxm1 + 1;
      idxp1p1 = idxp1 + 1;
      tmp = C0 * (orig[idxp1] + orig[idxm1]) + C1 * (orig[idx] + orig[idxp1p1] + orig[idxm1p1] + orig[idxm1m1]);
      sol[idx] = tmp;
    }
  }
}