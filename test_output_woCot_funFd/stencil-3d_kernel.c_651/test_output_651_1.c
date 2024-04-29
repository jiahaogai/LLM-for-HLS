#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long r;
  long q;
  long p;
  long pid;
  long c;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1;k < 40;k++) {...} */
  for (bound = 40 + 1; bound--; ) {
    k = 1 + bound;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    loopj:
/* Standardize from: for(j = 1;j < 40;j++) {...} */
    for (bound = 40 + 1; bound--; ) {
      j = 1 + bound;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 40;i++) {...} */
      for (bound = 40 + 1; bound--; ) {
        i = 1 + bound;
        pid = i - 1 + (j - 1) * 40 + (k - 1) * 1600;
        i_col = i - 1 + 40;
        j_col = j - 1 + 40 * 40;
        k_col = k - 1 + 40 * 40 * 40;
        sol[pid] = ((2 * orig[pid + 1]) + (2 * orig[pid + 40]) + (2 * orig[pid + 40 + 40]) + orig[pid + 40 + 40 * 2]) / 9 + ((1 * orig[pid + 1 + 40]) + (1 * orig[pid + 40 + 1]) + (1 * orig[pid + 40 + 40 * 2]) + (1 * orig[pid + 40 + 40 * 3])) / 4;
      }
    }
  }
}