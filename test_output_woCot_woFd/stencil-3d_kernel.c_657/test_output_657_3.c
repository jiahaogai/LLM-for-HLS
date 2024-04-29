#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32 - 1; k < 32 + 1 - 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32 - 1; j < 32 + 1 - 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32 - 1; i < 32 + 1 - 1; i++) {
        idx = i + (32 + 1) * (j + (32 + 1) * k);
        tmp = C0 * (orig[idx - 1 - (32 + 1) * (32 + 1)] + orig[idx + 1 - (32 + 1) * (32 + 1)] + orig[idx - (32 + 1) * (32 + 1)] + orig[idx + (32 + 1) * (32 + 1)]);
        tmp += C1 * (orig[idx - 1 - (32 + 1)] + orig[idx + 1 - (32 + 1)] + orig[idx - (32 + 1)] + orig[idx + (32 + 1)]);
        sol[idx] = tmp;
      }
    }
  }
}