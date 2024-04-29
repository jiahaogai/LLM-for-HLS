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
  long bound_col;
  long r;
  long q;
  long p;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k <= 40 + 0; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j <= 40 + 0; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i <= 40 + 0; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        bound = (40 << 2) + 1;
        bound_col = (40 << 1) + 1;
        r = i_col * bound_col + j_col * bound + k_col;
        q = i_col * bound_col + j_col * bound;
        p = i_col * bound_col + k_col;
        sol[r] = ((10 * orig[p]) + (1 * (orig[q] + orig[p + 1] + orig[p + bound] + orig[q + bound]))) / 42;
      }
    }
  }
}