#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{30}

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
  long idx_out;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k <= 32L + 1L - 1L; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j <= 32L + 1L - 1L; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i <= 32L + 1L - 1L; i++) {
        idx = i + (j - 1L) * 32L + (k - 1L) * 32L * 32L;
        idx_col = i - 1L + (j - 1L) * (1L + 32L) + (k - 1L) * 32L * (1L + 32L);
        idx_row = i + (j - 1L) * (1L + 32L) + (k - 1L) * (1L + 32L) * (1L + 32L);
        idx_in = idx_col + 32L * idx_row;
        idx_out = idx;
        sol[idx_out] = ((2L * orig[idx_in]) + (C0 * (orig[idx_in - 1L] + orig[idx_in + 1L])) + (C1 * (orig[idx_in - 32L] + orig[idx_in + 32L])) + (C0 * (orig[idx_in - 32L - 1L] + orig[idx_in + 32L - 1L])) + (C1 * (orig[idx_in - 32L + 1L] + orig[idx_in + 32L + 1L]))) / (2L + C0 + C1);
      }
    }
    loop_k_col:
/* Standardize from: for(k_col = 1; k_col < 32 + 1 - 1; k_col++) {...} */
    for (k_col = 1L + 32L; k_col <= 32L + 1L - 1L; k_col++) {
      idx_col = idx_col + 1L;
      idx_out = idx_out + 1L;
      sol[idx_out] = ((2L * sol[idx_out]) + (C0 * (sol[idx_out - 1L] + sol[idx_out + 1L])) + (C1 * (sol[idx_out - 32L] + sol[idx_out + 32L])) + (C0 * (sol[idx_out - 32L - 1L] + sol[idx_out + 32L - 1L])) + (C1 * (sol[idx_out - 32L + 1L] + sol[idx_out + 32L + 1L]))) / (2L + C0 + C1);
    }
    k_row = k - 32L;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j_col:
/* Standardize from: for(j_col = 1; j_col < 32 + 1 - 1; j_col++) {...} */
    for (j_col = 1L + 32L; j_col <= 32L + 1L - 1L; j_col++) {
      idx_row = idx_row + 1L;
      idx_out = idx_out + 1L;
      sol[idx_out] = ((2L * sol[idx_out]) + (C0 * (sol[idx_out - 1L] + sol[idx_out + 1L])) + (C1 * (sol[idx_out - 32L] + sol[idx_out + 32L])) + (C0 * (sol[idx_out - 32L - 1L] + sol[idx_out + 32L - 1L])) + (C1 * (sol[idx_out - 32L + 1L] + sol[idx_out + 32L + 1L]))) / (2L + C0 + C1);
    }
  }
}