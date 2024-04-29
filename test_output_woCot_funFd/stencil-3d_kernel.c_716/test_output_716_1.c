#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 1;j++) {...} */
  for (j = 1 + 32 - 1; j-- > 1 + 0; ) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 1;k++) {...} */
    for (k = 1 + 32 - 1; k-- > 1 + 0; ) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{3}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 1;i++) {...} */
      for (i = 1 + 32 - 1; i-- > 1 + 0; ) {
        idx = i + (j + (k + 1 * 32 + 1) * 32) * 392;
        s = orig[idx] + ((+1 + 32 * 32) * orig[idx + 32] + (+32 + 0 * 32) * orig[idx + 1]) + ((+0 + 32 * 31) * orig[idx - 32] + (+1 + 0 * 31) * orig[idx + 31]);
        sol[idx] = s;
      }
    }
  }
}