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
  long idxm2;
  long idxp1;
  long idxp2;
  long idxm1p1;
  long idxm1p2;
  long idxm2p1;
  long idxm2p2;
  long idxp1p1;
  long idxp1p2;
  long idxp2p1;
  long idxp2p2;
  long val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
/* Standardize from: for(i = 1; i < 32 + 1; i++) {...} */
  for (i = 1 + 32; i-- > 1 + 0; ) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1; j++) {...} */
    for (j = 1 + 32; j-- > 1 + 0; ) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
/* Standardize from: for(k = 1; k < 32 + 1; k++) {...} */
      for (k = 1 + 32; k-- > 1 + 0; ) {
        idx = i * (1 + 32) * (1 + 32) + j * (1 + 32) + k;
        idxm1 = idx - (1 + 32);
        idxm2 = idx - (1 + 32) * (1 + 32);
        idxp1 = idx + (1 + 32);
        idxp2 = idx + (1 + 32) * (1 + 32);
        idxm1p1 = idxm1 + (1 + 32);
        idxm1p2 = idxm1 + (1 + 32) * (1 + 32);
        idxm2p1 = idxm2 + (1 + 32);
        idxm2p2 = idxm2 + (1 + 32) * (1 + 32);
        idxp1p1 = idxp1 + (1 + 32);
        idxp1p2 = idxp1 + (1 + 32) * (1 + 32);
        idxp2p1 = idxp2 + (1 + 32);
        idxp2p2 = idxp2 + (1 + 32) * (1 + 32);
        val = orig[idx] + C0 * (orig[idxm1] + orig[idxm2] + orig[idxp1] + orig[idxp2]) + C1 * (orig[idxm1p1] + orig[idxm1p2] + orig[idxm2p1] + orig[idxm2p2] + orig[idxp1p1] + orig[idxp1p2] + orig[idxp2p1] + orig[idxp2p2]);
        sol[idx] = val;
      }
    }
  }
}