#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int flatten_index;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj_stencil:
/* Standardize from: for(j = 0; j < 32; j++) {...} */
  for (j = 0; j <= 31 - 1; j++) {
     loopk_stencil:
/* Standardize from: for(k = 0; k < 32; k++) {...} */
    for (k = 0; k <= 31 - 1; k++) {
      i_col = -1 * pad + 0 + (32 * j);
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopj_col:
      for (j_col = 0; j_col <= 31 - 1; j_col++) {
        k_col = -1 * pad + 0 + (32 * k);
        flatten_index = i_col + k_col;
        sol[flatten_index] = ((filter[0] * orig[flatten_index]) + (filter[1] * (orig[flatten_index + 1])) + (filter[2] * (orig[flatten_index + 2])) + (filter[3] * (orig[flatten_index + 3])) + (filter[4] * (orig[flatten_index + 4])) + (filter[5] * (orig[flatten_index + 5])) + (filter[6] * (orig[flatten_index + 6])) + (filter[7] * (orig[flatten_index + 7])) + (filter[8] * (orig[flatten_index + 8]))) / 256;
      }
    }
  }
}