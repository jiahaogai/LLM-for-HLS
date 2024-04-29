#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long ko;
  long ki;
  long jj;
  long ij;
  long kj;
  long kk;
  long idx;
  long idxm1;
  long idxp1;
  long idxes;
  long idxm1p1;
  long idxm1m1;
  long idxp1p1;
  long idxp1m1;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
/* Standardize from: for(i = 1; i < 32; i++) {...} */
  for (i = 1 + 0; i < 33 + 0; i++ ) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 1; j < 32; j++) {...} */
    for (j = 1 + 0; j < 33 + 0; j++ ) {
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      loop_k:
/* Standardize from: for(k = 1; k < 32; k++) {...} */
      for (k = 1 + 0; k < 33 + 0; k++ ) {
        idx = i * 33 * 33 + j * 33 + k;
        idxm1 = idx - 33;
        idxp1 = idx + 33;
        idxes = idx + 1;
        idxm1p1 = idxm1 + 1;
        idxm1m1 = idxm1 - 1;
        idxp1p1 = idxp1 + 1;
        idxp1m1 = idxp1 - 1;
        tmp = orig[idx] + C0 * (orig[idxm1] + orig[idxp1] + orig[idxes] + orig[idxm1p1] + orig[idxm1m1] + orig[idxp1p1] + orig[idxp1m1]);
        sol[idx] = tmp;
      }
    }
  }
}