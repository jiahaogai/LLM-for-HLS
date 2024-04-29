Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int flatten_i;
  int flatten_j;
  int flatten_k;
  int idx;
  int val;
  int temp[9];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  loopj_stencil:
/* Standardize from: for(j = 0;j < 64;j++) {...} */
  for (j = 0; j <= 63 - 1; j += 1) {
    j_col = j << 3;
    loopk_stencil:
/* Standardize from: for(k = 0;k < 128;k++) {...} */
    for (k = 0; k <= 127 - 1; k += 1) {
      k_col = k << 3;
      flatten_i = 0 + 8192 * (k + 2);
      flatten_j = 1 + 64 * (j + 2);
      flatten_k = 0 + 8 * (k + 2);
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopidx_stencil:
      for (idx = 0; idx <= 7; idx += 1) {
        val = 0;
        loopk2_stencil:
        for (k2 = 0; k2 <= 2; k2 += 1) {
          loopj2_stencil:
          for (j2 = 0; j2 <= 2; j2 += 1) {
            i = k_col + flatten_j2[j2];
            val += filter[flatten_k2[k2]] * orig[flatten_i + i];
          }
        }
        temp[idx] = val;
      }
      loopidx_1_stencil:
      for (idx = 0; idx <= 7; idx += 1) {
        sol[flatten_j + idx] = temp[idx];
      }
    }
  }
}