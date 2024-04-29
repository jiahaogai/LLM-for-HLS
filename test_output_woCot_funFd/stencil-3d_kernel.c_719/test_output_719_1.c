#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}

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
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j <= 392 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1; k <= 392 - 1; k++) {
      idx = (392 * 392) * j + 392 * k;
      idxm1 = idx - 392;
      idxp1 = idx + 392;
      idxm1m1 = idxm1 - 392;
      idxm1p1 = idxm1 + 392;
      idxp1p1 = idxp1 + 392;
      tmp = C0 * (orig[idxp1] - (2 * orig[idx]) + orig[idxm1]);
      tmp += C1 * (orig[idxp1p1] - (2 * orig[idxm1p1]) + orig[idxm1m1]);
      sol[idx] = tmp;
    }
  }
}