The error(s) occurred in the kernel: stencil3d.

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
/* Standardize from: for(j = 1;j < 32 + 1 - 2;j++) {...} */
  for (j = 1 + 32L; j >= 32L; j--) {
     loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 2;k++) {...} */
    for (k = 1 + 32L; k >= 32L; k--) {
      idx = ((32L + 1L) * (32L + 1L) * j) + ((32L + 1L) * k) + 1L;
      idxm1 = ((32L + 1L) * (32L + 1L) * (j - 1L)) + ((32L + 1L) * (k - 1L)) + 1L;
      idxp1 = ((32L + 1L) * (32L + 1L) * (j + 1L)) + ((32L + 1L) * (k + 1L)) + 1L;
      idxm1m1 = ((32L + 1L) * (32L + 1L) * (j - 1L)) + ((32L + 1L) * (k - 1L)) + 1L;
      idxm1p1 = ((32L + 1L) * (32L + 1L) * (j - 1L)) + ((32L + 1L) * (k + 1L)) + 1L;
      idxp1p1 = ((32L + 1L) * (32L + 1L) * (j + 1L)) + ((32L + 1L) * (k + 1L)) + 1L;
      tmp = C0 * (orig[idxp1p1] + orig[idxp1] + orig[idxp1m1] + orig[idx] + orig[idxm1p1] + orig[idxm1] + orig[idxm1m1]);
      tmp += C1 * (orig[idxp1p1 + 1L] + orig[idxp1 + 1L] + orig[idxp1m1 + 1L] + orig[idx + 1L] + orig[idxm1p1 + 1L] + orig[idxm1 + 1L] + orig[idxm1m1 + 1L]);
      sol[idx] = tmp;
    }
  }
}