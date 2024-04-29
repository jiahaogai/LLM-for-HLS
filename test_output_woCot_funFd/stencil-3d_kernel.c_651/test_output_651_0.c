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
  long s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 3;j++) {...} */
  for (j = 1 + 32 - 1; j < 32 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
    for (k = 1 + 32 - 1; k < 32 + 1; k++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{3}
      loopi:
/* Standardize from: for(i = 1;i < 32 + 1 - 3;i++) {...} */
      for (i = 1 + 32 - 1; i < 32 + 1; i++) {
        i_col = i - 1 + ((j - 1) * 32) + ((k - 1) * 32 * 32);
        j_col = j - 1 + ((k - 1) * 32);
        k_col = k - 1;
        r = ((((k_col) * 32) + (j_col)) * 32) + (i_col);
        s = (((k_col - 1) * 32) + (j_col)) * 32;
        q = ((k_col - 1) * 32) + (j_col - 1);
        p = (k_col - 1) * 32;
        bound = 32 * 32 * 32;
        if (r < bound) {
          orig[r] = sol[r] - ((C0 * (sol[r - 1] - sol[r + 1])) + (C1 * (sol[s - 32] - sol[s + 32]) + (sol[q - 1] - sol[q + 1])));
        }
      }
    }
  }
}