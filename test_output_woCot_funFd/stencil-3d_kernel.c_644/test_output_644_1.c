#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1;j++) {...} */
  for (j = 1; j <= 32; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1;k++) {...} */
    for (k = 1; k <= 32; k++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1;i++) {...} */
      for (i = 1; i <= 32; i++) {
        idx = i + ((32 + 2) * (k + (32 + 2) * j));
        temp = C0 * (orig[idx - 1] + orig[idx + 1] + ((32 + 2) * (orig[idx - (32 + 2)] + orig[idx + (32 + 2)])));
        temp += C1 * orig[idx];
        sol[idx] = temp;
      }
    }
  }
}