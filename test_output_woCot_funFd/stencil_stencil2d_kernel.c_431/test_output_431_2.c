#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int col;
  int flit_i;
  int flit_j;
  int out_i;
  int out_j;
  int in_i;
  int in_j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1; j < 33 - 1; j++) {...} */
  for (j = 1 + 32; j-- > 32 - 1; ) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
/* Standardize from: for(i = 1; i < 32 - 1; i++) {...} */
    for (i = 1 + 31; i-- > 31 - 1; ) {
      k_col = -1 * 32;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopk:
      for (k = 0; k < 32 * 32; k++) {
        flit_i = k_col + i;
        flit_j = k + 1;
        if (flit_i >= 0 && flit_i < 32 && flit_j >= 0 && flit_j < 32) {
          orig[k] = 1 * orig[flit_j * 32 + flit_i];
        }
        ++k_col;
      }
      out_i = i - 1;
      out_j = -1 * 32 + 31;
      in_i = 16 * 32 + i - 1;
      in_j = 16 + 31;
      sol[out_j * 32 + out_i] = 0;
/*#pragma ACCEL PARALLEL FACTOR=auto{4}*/
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopk_col:
      for (k_col = 0; k_col < 9; k_col++) {
        k = k_col;
        out_j = 32 * (k_col - 4) + out_i;
        in_j = 32 * (k_col - 4) + in_i;
        sol[out_j] += filter[k_col] * orig[in_j];
      }
    }
  }
}