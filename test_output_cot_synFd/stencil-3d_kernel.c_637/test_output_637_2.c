**TODO:**
- The last few loops in this kernel are not parallelized because the workload is too small. You may want to increase the size of the workload to see a speedup from parallelization.

#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long j_col;
  long k_row;
  long i_row;
  long j_row;
  long idx;
  long idx_col;
  long idx_row;
  long idx_in;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32 + 1L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j < 32 + 1L; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i < 32 + 1L; i++) {
        idx = i + (j + (k * 32L)) * 32L;
        idx_col = i - 1L + (j + (k * 32L)) * 32L;
        idx_row = i + (j - 1L + (k * 32L)) * 32L;
        idx_in = i + (j + (k - 1L + 32L) * 32L);
        t = orig[idx] + 3L * (orig[idx_col] + orig[idx_row] + orig[idx_in]);
        sol[idx] = t;
      }
    }
  }
}