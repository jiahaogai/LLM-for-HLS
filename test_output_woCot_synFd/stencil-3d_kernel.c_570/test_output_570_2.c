#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long tid;
  long orig_idx;
  long sol_idx;
  long block_size;
  long block_mask;
  long pad_size;
  long pad_mask;
  long block_idx;
  long i_pad;
  long j_pad;
  long k_pad;
  long k_col_pad;
  long i_col_pad;
  long v;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_j:
/* Standardize from: for(j = 1;j < 32 + 1 - 3;j++) {...} */
  for (j = 1 + 32 - 1; j < 32 + 1; j++) {
     loop_k:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
    for (k = 1 + 32 - 1; k < 32 + 1; k++) {
      loop_k_col:
/* Standardize from: for(k_col = 1;k_col < 32 + 1;k_col++) {...} */
      for (k_col = 1; k_col < 32 + 1; k_col++) {
        loop_i_col:
/* Standardize from: for(i_col = 1;i_col < 32 + 1;i_col++) {...} */
        for (i_col = 1; i_col < 32 + 1; i_col++) {
          v = 0;
          loop_tid:
/* Standardize from: for(tid=0;tid < 1;tid++) {...} */
          for (tid = 0; tid < 1; tid++) {
            i_pad = i - 1 + tid * 1;
            j_pad = j - 1 + tid * 0;
            k_pad = k - 1 + tid * 0;
            k_col_pad = k_col - 1 + tid * 1;
            i_col_pad = i_col - 1 + tid * 1;
            orig_idx = i_pad * 32 * 32 + j_pad * 32 + k_pad;
            sol_idx = k_col_pad * 1 * 32 * 32 + i_col_pad * 1 * 32 + v;
            v = orig[orig_idx] + ((k_col == 1 ? 0 : -1 * (orig[orig_idx + 32] + orig[orig_idx + 32 * (32 - 1)]))) + ((i_col == 1 ? 0 : -1 * (orig[orig_idx + 1] + orig[orig_idx + 32 * (32 - 1)]))) + ((k_col == 32 ? 0 : -1 * (orig[orig_idx + 32 * (32 + 1)] + orig[orig_idx + 32 * (32 - 1)])));
            sol[sol_idx] = v;
          }
        }
      }
    }
  }
}