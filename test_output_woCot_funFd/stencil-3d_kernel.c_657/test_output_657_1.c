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
  long t1;
  long t2;
  long t3;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loop_j:
/* Standardize from: for(j = 1;j < 32 + 1;j++) {...} */
  for (j = 1 + 32;j -- > 32 + 1; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_k:
/* Standardize from: for(k = 1;k < 32 + 1;k++) {...} */
    for (k = 1 + 32;k -- > 32 + 1; ) {
      idx = (((32 + 1) * 32) * k) + (32 * j) + 1;
      idxm1 = idx - 1;
      idxp1 = idx + 1;
      idxm1m1 = idxm1 - 1;
      idxm1p1 = idxm1 + 1;
      idxp1p1 = idxp1 + 1;
      t1 = orig[idxm1m1] + orig[idxm1p1] + orig[idxp1p1];
      t2 = orig[idxm1p1] + orig[idxp1p1];
      t3 = orig[idxm1m1] + t1;
      sol[idx] = ((C0 - t2) - t3);
    }
  }
}