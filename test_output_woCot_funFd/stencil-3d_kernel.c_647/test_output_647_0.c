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
        ko = (32 * (i - 1)) + 1;
        kj = (32 * (j - 1)) + 1;
        ki = (32 * (k - 1)) + 1;
        val = ((C0 * (orig[ko - 1] + orig[ko + 1] + orig[kj - 1] + orig[kj + 1] + orig[ki - 1] + orig[ki + 1] - 7 * orig[ko + kj + ki] )) + (C1 * orig[ko + kj + ki])) / 8;
        sol[ko + kj + ki] = val;
      }
    }
  }
}