#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long k_row;
  long j_row;
  long i_row;
  long idx;
  long idx_col;
  long idx_row;
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k <= 32L + 32L; k++) {
     k_col = vect_contact(k,32L);
     loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2L; j <= 32L + 2L; j++) {
      j_col = vect_contact(j,32L);
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1L; i <= 32L + 1L; i++) {
        i_col = vect_contact(i,32L);
        i_row = i - 1L;
        j_row = j - 1L;
        k_row = k - 1L;
        idx_col = i_col;
        idx_row = i_row * 32L;
        idx = idx_col + idx_row;
        sum = ((orig[idx_col + ((j_row * 32L) + k_row) * 32L] + orig[idx_col + ((j_row * 32L) + k_row + 1L) * 32L]) + orig[idx_col + ((j_row + 1L) * 32L + k_row) * 32L]) + orig[idx_col + ((j_row + 1L) * 32L) + (k_row + 1L) * 32L];
        sum += ((orig[idx_col + ((j_row * 32L) + k_row) * 32L + 32L] + orig[idx_col + ((j_row * 32L) + k_row + 1L) * 32L + 32L]) + orig[idx_col + ((j_row + 1L) * 32L + k_row) * 32L + 32L]) + orig[idx_col + ((j_row + 1L) * 32L) + (k_row + 1L) * 32L + 32L];
        sum /= 8L;
        sol[idx] = sum;
      }
    }
  }
}