Code: #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long pad_j;
  long pad_i;
  long pad_k;
  long j_col_start;
  long j_col_end;
  long i_col_start;
  long i_col_end;
  long k_col_start;
  long k_col_end;
  long index;
  long index_col;
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  pad_j = 1;
  pad_i = 1;
  pad_k = 1;
  j_col_start = 0;
  j_col_end = 32 + 1;
  i_col_start = 0;
  i_col_end = 32 + 1;
  k_col_start = 0;
  k_col_end = 32 + 1;
  loop_j:
/* Standardize from: for(j = 1;j < 33;j++) {...} */
  for (j = 1 + 32 + 1; j-- > 1 + 0 + 1; ) {
    loop_i:
/* Standardize from: for(i = 1;i < 33;i++) {...} */
    for (i = 1 + 32 + 1; i-- > 1 + 0 + 1; ) {
      loop_k:
/* Standardize from: for(k = 1;k < 33;k++) {...} */
      for (k = 1 + 32 + 1; k-- > 1 + 0 + 1; ) {
        pad_k = 33 + 1 - k;
        pad_i = 33 + 1 - i;
        pad_j = 33 + 1 - j;
        index = ((pad_k * (33 + 1) + pad_i) * (33 + 1) + pad_j) - 1;
        sum = 0;
        loop_k_col:
/* Standardize from: for(k_col = 0;k_col < 33;k_col++) {...} */
        for (k_col = 0; k_col < 33 + 0; k_col++) {
          loop_i_col:
/* Standardize from: for(i_col = 0;i_col < 33;i_col++) {...} */
          for (i_col = 0; i_col < 33 + 0; i_col++) {
            pad_i_col = i + i_col - 1;
            pad_k_col = k + k_col - 1;
            index_col = ((pad_k_col * (33 + 1) + pad_i_col) * (33 + 1) + pad_j) - 1;
            sum += orig[index_col] * mask3d[k_col * 33 + i_col];
          }
        }
        sol[index] = sum;
      }
    }
  }
}