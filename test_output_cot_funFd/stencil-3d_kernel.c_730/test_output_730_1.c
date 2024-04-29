Code: 
 #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long ko;
  long kf;
  long jj;
  long ii;
  long idx;
  long idxm1;
  long idxp1;
  long idxm1m1;
  long idxm1p1;
  long idxp1p1;
  long idxp1m1;
  long C;
  long D;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  loop_i:
/* Standardize from: for(i = 1; i < 32 + 1; i++) {...} */
  for (i = 1 + 32; --i > 0 + 1; ) {
     loop_j:
/* Standardize from: for(j = 1; j < 32 + 1; j++) {...} */
    for (j = 1 + 32; --j > 0 + 1; ) {
      loop_k:
/* Standardize from: for(k = 1; k < 32 + 1; k++) {...} */
      for (k = 1 + 32; --k > 0 + 1; ) {
        ko = (32 * (32 * k + j)) + i;
        kf = (32 * (32 * (k + 1) + j)) + i;
        jj = 32 * j + 1;
        ii = 32 * i + 1;
        idx = ko * 32 + 1;
        idxm1 = ko * 32 - 1;
        idxp1 = ko * 32 + 33;
        idxm1m1 = ko * 32 - 33;
        idxm1p1 = ko * 32 - 16;
        idxp1p1 = ko * 32 + 16;
        idxp1m1 = ko * 32 + 32;
        C = orig[ko] + orig[kf] + orig[idxm1m1] + orig[idxm1] + orig[idxm1p1] + orig[idxp1m1] + orig[idxp1] + orig[idxp1p1];
        D = C0 * (orig[idx] + orig[idxp1 + 1] + orig[idxm1 + 1] - orig[idxp1m1]) + C1 * (orig[idxp1] - orig[idxm1]);
        sol[ko] = D;
      }
    }
  }
}