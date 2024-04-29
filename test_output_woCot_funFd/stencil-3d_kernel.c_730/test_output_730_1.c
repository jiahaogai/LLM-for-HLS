Code: 
 #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long ko;
  long ki;
  long kj;
  long i_col;
  long j_col;
  long k_col;
  long idx;
  long idx_col;
  long t1;
  long t2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  loop_i:
/* Standardize from: for(i = 1; i < 32 + 1; i++) {...} */
  for (i = 1l; i <= 32l; i++ ) {
     loop_j:
/* Standardize from: for(j = 1; j < 32 + 1; j++) {...} */
    for (j = 1l; j <= 32l; j++ ) {
       loop_k:
/* Standardize from: for(k = 1; k < 32 + 1; k++) {...} */
      for (k = 1l; k <= 32l; k++ ) {
        ko = (32l + 1l) * (32l + 1l) * k - 32l * (32l + 1l) + j - 1l;
        ki = (32l + 1l) * k - 32l * 1l;
        kj = (32l + 1l) * j - 32l * (32l + 1l);
        i_col = i - 1l;
        j_col = j - 1l;
        k_col = k - 1l;
        idx = i_col * (32l + 1l) * (32l + 1l) + j_col * (32l + 1l) + k_col;
        idx_col = ki * 32l + kj;
        t1 = orig[idx] + C0 * (orig[idx_col] + orig[idx_col + 1l]);
        t2 = C1 * (sol[idx_col] + sol[idx_col + 1l]);
        sol[idx] = t1 - t2;
      }
    }
  }
}