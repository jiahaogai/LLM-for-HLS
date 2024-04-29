The`#pragma ACCEL PIPELINE auto{off}` and `#pragma ACCEL TILE FACTOR=auto{4}` directives specify that this loop should not be automatically pipelined, but should be kept whole and tiled with a factor of 4. The`#pragma ACCEL PIPELINE auto{off}` and `#pragma ACCEL TILE FACTOR=auto{1}` directives specify that the nested loop should not be automatically pipelined, but should be kept whole and unrolled with a factor of 1. The`#pragma ACCEL PARALLEL FACTOR=auto{2}` directive specifies that loop iterations should be executed in parallel with a factor of 2.

### #pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{4}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        idx = i + ((j - 1) * 40) + ((k - 1) * 40 * 40);
        idx_col = i - 1 + ((j - 1) * (40 - 2)) + ((k - 1) * (40 - 2) * (40 - 2));
        t = 0;
        loop_k_col:
/* Standardize from: for(k_col = 1; k_col < 40; k_col++) {...} */
        for (k_col = 1 + 0; k_col < 40 + 0; k_col++) {
          loop_j_col:
/* Standardize from: for(j_col = 1; j_col < 40; j_col++) {...} */
          for (j_col = 1 + 0; j_col < 40 + 0; j_col++) {
            i_col = i_col + 1;
            t = t + orig[idx_col + ((j_col - 1) * 40) + ((k_col - 1) * 40 * 40)] * C0;
          }
          j_col = 0;
        }
        k_col = 0;
        sol[idx] = t / C1;
      }
      i = 0;
    }
    j = 0;
  }
  k = 0;
}