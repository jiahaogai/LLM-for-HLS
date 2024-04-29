#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j <= 391L; j++) {
    long j_col_tmp = j;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1; k <= 391L; k++) {
      long k_col_tmp = k;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1; i <= 391L; i++) {
        long i_col_tmp = i;
        long idx = i + ((j + (k * 392L)) * 392L);
        buf = ((C0 * orig[idx]) + (C1 * (orig[idx + 392L] + orig[idx - 392L]))) + (orig[idx + 392L * 392L] + orig[idx - 392L * 392L]);
        sol[idx] = buf;
      }
    }
  }
}