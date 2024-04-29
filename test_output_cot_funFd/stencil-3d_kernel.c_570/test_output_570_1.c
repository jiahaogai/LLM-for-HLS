#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
     k_col = k - 1 + 16L;
     loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      i_col = j - 1 + 16L;
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 32L; i > 1L; i--) {
        idx = i + 16L + ((j - 1) + 16L) * (1L + 32L) + ((k - 1) + 16L) * ((1L + 32L) * (1L + 32L));
        tmp = orig[idx - 1] + orig[idx] + orig[idx + 1] + orig[idx + 16L] + orig[idx + 32L] + orig[idx + 48L] + orig[idx + 64L] + orig[idx + 80L] + orig[idx + 96L] + orig[idx + 112L];
        sol[idx] = tmp;
      }
      sol[idx + 1L] = 0L;
    }
    sol[idx + 32L] = 0L;
  }
  loop_k_1:
/* Standardize from: for(k = 32 + 1 - 3; k < 32 + 1; k++) {...} */
  for (k = 32L; k < 32L + 1L; k++) {
     k_col = k - 1 + 16L;
     loop_j_1:
/* Standardize from: for(j = 32 + 1 - 2; j < 32 + 1; j++) {...} */
    for (j = 32L; j < 32L + 1L; j++) {
      i_col = j - 1 + 16L;
      loop_i_1:
/* Standardize from: for(i = 32 + 1 - 1; i < 32 + 1; i++) {...} */
      for (i = 32L; i < 32L + 1L; i++) {
        idx = i + 16L + ((j - 1) + 16L) * (1L + 32L) + ((k - 1) + 16L) * ((1L + 32L) * (1L + 32L));
        tmp = orig[idx] + orig[idx + 1L] + orig[idx + 16L] + orig[idx + 32L] + orig[idx + 48L] + orig[idx + 64L] + orig[idx + 80L] + orig[idx + 96L] + orig[idx + 112L] + orig[idx + 128L];
        sol[idx] = tmp;
      }
    }
  }
}