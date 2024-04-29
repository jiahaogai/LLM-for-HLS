#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long index;
  long k_row;
  long j_row;
  long i_row;
  long end_k;
  long end_j;
  long end_i;
  long src_k;
  long src_j;
  long src_i;
  long dst_k;
  long dst_j;
  long dst_i;
  long C0_v;
  long C1_v;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 1; k++) {...} */
  for (k = 1 + 32L; k-- > 32L + 1L; ) {
    k_col = k;
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 1; j++) {...} */
    for (j = 1 + 32L; j-- > 32L + 1L; ) {
      j_col = j;
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 32L; i-- > 32L + 1L; ) {
        i_col = i;
        index = (((k_col) * 32L) + (j_col)) * 32L + (i_col);
        k_row = k - 1L;
        j_row = j - 1L;
        i_row = i - 1L;
        end_k = (32L > (32L + 1L - k_row)) ? 32L : (32L + 1L - k_row);
        end_j = (32L > (32L + 1L - j_row)) ? 32L : (32L + 1L - j_row);
        end_i = (32L > (32L + 1L - i_row)) ? 32L : (32L + 1L - i_row);
        src_k = k_row * 32L + j_row * 32L + i_row;
        loop_k_row:
        for (; k_row < end_k; k_row++) {
          src_j = k_row * 32L + j_row * 32L + i_row;
          loop_j_row:
          for (j_row = 0L; j_row < end_j; j_row++) {
            src_i = src_j + i_row;
            loop_i_row:
            for (i_row = 0L; i_row < end_i; i_row++) {
              dst_k = (k_col) * 32L + (j_col) * 32L + i_col;
              dst_j = dst_k + j_col;
              dst_i = dst_j + i_col;
              C0_v = C0;
              C1_v = C1;
              sol[dst_i] = ((C0_v * orig[src_i]) + (C1_v * (orig[dst_i] + orig[src_j] + orig[src_k] + orig[dst_j] + orig[dst_k]))) >> 15;
            }
          }
        }
      }
    }
  }
}