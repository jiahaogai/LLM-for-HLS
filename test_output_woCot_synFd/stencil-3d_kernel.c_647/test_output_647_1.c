#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long ko;
  long kj;
  long ki;
  long p;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
/* Standardize from: for(i = 1; i < 32; i++) {...} */
  for (i = 1l + 32l; i > 1l; i--) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 1; j < 32; j++) {...} */
    for (j = 1l + 32l; j > 1l; j--) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
/* Standardize from: for(k = 1; k < 32; k++) {...} */
      for (k = 1l + 32l; k > 1l; k--) {
        ko = ((32l + 2l) * (32l + 2l)) * (k - 1l);
        kj = ((32l + 2l) * (k - 1l)) + 1l;
        ki = (kj + (32l + 2l)) + 1l;
        sol[ko] = C0 * orig[ko] + C1 * (orig[kj] + orig[ki] + orig[kj + 1l] + orig[ki + 1l]);
      }
    }
  }
}