#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long ko;
  long kj;
  long ki;
  long val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
/* Standardize from: for(i = 1; i < 32; i++) {...} */
  for (i = 1; i < 33; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 1; j < 32; j++) {...} */
    for (j = 1; j < 33; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      loop_k:
/* Standardize from: for(k = 1; k < 32; k++) {...} */
      for (k = 1; k < 33; k++) {
        ko = ((32 + 2) * (32 + 2) * (k - 1)) + ((32 + 2) * (j - 1)) + (i - 1);
        kj = ((32 + 2) * (j - 1)) + (i - 1);
        ki = (i - 1);
        val = (((C0 * ((orig[ko] + orig[ko + 1]) + (orig[ko + 32] + orig[ko + 33]))) + ((C1 * ((orig[kj] + orig[kj + 1]) + (orig[kj + 32] + orig[kj + 33]))) + (((orig[ki] + orig[ki + 1]) + (orig[ki + 32] + orig[ki + 33]))))) / (C0 + C1)) + orig[ko];
        sol[ko] = val;
      }
    }
  }
}