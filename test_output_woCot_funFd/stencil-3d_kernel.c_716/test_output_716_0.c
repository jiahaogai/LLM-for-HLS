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
  long delta;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1 + 0; j <= 392 + 0; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    loopk_col:
    for (k_col = 1 + 0; k_col <= 32 + 0; k_col++) {
      buf = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{3}
      loopi_col:
      for (i_col = 1 + 0; i_col <= 32 + 0; i_col++) {
        buf += orig[index(i_col, j, k_col)];
      }
      delta = buf + ((32 + 0) * (31 + 0)) / 2 - sol[index(0, j, k_col)];
      sol[index(0, j, k_col)] = buf;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
    for (k = 1 + 0; k < 32 + 0; k++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
      for (i = 1 + 0; i < 32 + 0; i++) {
        buf = 0;
        buf += sol[index(i - 1, j, k)];
        buf += sol[index(i + 1, j, k)];
        buf += sol[index(i, j - 1, k)];
        buf += sol[index(i, j + 1, k)];
        buf += sol[index(i, j, k - 1)];
        buf += sol[index(i, j, k + 1)];
        delta = buf - sol[index(i, j, k)];
        sol[index(i, j, k)] = buf / 65536 + delta / 4;
      }
    }
  }
}