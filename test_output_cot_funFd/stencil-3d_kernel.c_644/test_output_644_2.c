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
  long C02;
  long C12;
  C02 = C0 + 2;
  C12 = C1 + 2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
  for (j = 0; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loopk:
    for (k = 0; k < 33; k++) {
      loopi:
      for (i = 0; i < 32; i++) {
        idx = i + 32 * (k + 32 * j);
        idxm1 = idx - 1;
        idxp1 = idx + 1;
        idxm1m1 = idxm1 - 1;
        idxm1p1 = idxm1 + 1;
        idxp1p1 = idxp1 + 1;
        idxp1m1 = idxp1 - 1;
        sol[idx] = ((C0 * orig[idx]) - (C1 * (orig[idxm1] + orig[idxp1] + orig[idxm1m1] + orig[idxm1p1] + orig[idxp1p1] + orig[idxp1m1])));
      }
    }
  }
}