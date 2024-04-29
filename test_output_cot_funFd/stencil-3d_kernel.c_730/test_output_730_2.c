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
  long idx_orig;
  long idx_sol;
  long C0_2;
  long C1_2;
  C0_2 = C0 * 2;
  C1_2 = C1 * 2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  loop_i:
/* Standardize from: for(i = 1; i < 32 + 1; i++) {...} */
  for (i = 1 + 32; --i > 0 + 1; ) {
     loop_j:
/* Standardize from: for(j = 1; j < 32 + 1; j++) {...} */
    for (j = 1 + 32; --j > 0 + 1; ) {
       loop_k:
/* Standardize from: for(k = 1; k < 32 + 1; k++) {...} */
      for (k = 1 + 32; --k > 0 + 1; ) {
        ko = (32 + 1) * (32 + 1) * k;
        ki = (32 + 1) * k;
        kj = 32 + 1 * j;
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        idx = ko + ki + kj;
        idx_orig = i_col * ki + j_col * kj + k_col;
        idx_sol = idx;
        sol[idx_sol] = ((C0_2 * orig[idx_orig]) + (C1_2 * (orig[idx_orig + ki] + orig[idx_orig + kj] + orig[idx_orig + ki + kj]))) / C0;
      }
    }
  }
}