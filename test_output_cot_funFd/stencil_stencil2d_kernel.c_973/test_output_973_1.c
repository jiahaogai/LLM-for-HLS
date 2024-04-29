#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int r;
  int c;
  int r_col_start;
  int r_col_end;
  int c_col_start;
  int c_col_end;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loopj_col:
/* Standardize from: for(j_col = 1;j_col < 64 + 2;j_col++) {...} */
  for (j_col = 1; j_col < 64 + 2; j_col++) {
    int _in_j_col = 0 + 64 * (j_col - 1);
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopk_col:
/* Standardize from: for(k_col = 1;k_col < 3;k_col++) {...} */
    for (k_col = 1; k_col < 3; k_col++) {
      int _in_k_col = 64 * (k_col - 1);
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 0;i < 128;i++) {...} */
      for (i = 0; i < 128; i++) {
        int _in_i = 1 * i;
        int _out_j = 0 + 64 * (j_col - 1);
        int _tmp_0 = 0 + _out_j;
        sol[_tmp_0] = ((2 * orig[_in_i + _in_j_col]) + (2 * orig[_in_i + 1 + _in_j_col]) + (2 * orig[_in_i + 2 + _in_j_col]) + orig[_in_i + 3 + _in_j_col] + filter[k_col]) / 8;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 0;j < 64;j++) {...} */
  for (j = 0; j < 64; j++) {
    int _in_j = 1 * j;
    int _out_j = 1 * j;
    loopk:
/* Standardize from: for(k = 0;k < 3;k++) {...} */
    for (k = 0; k < 3; k++) {
      int _in_k = 64 * (k - 1);
      r_col_start = (0 - 1) + _in_k;
      r_col_end = (128 - 1) + _in_k;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopc_col:
      for (c_col = r_col_start; c_col < r_col_end; c_col++) {
        i_col = c_col;
        int _in_i_col = 1 * i_col