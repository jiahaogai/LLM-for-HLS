#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj_col:
/* Standardize from: for(j_col = 0;j_col < 9;j_col++) {...} */
  for (j_col = 0; j_col <= 8; j_col++) {
    int _in_j_col = 0 + 8L * j_col;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopi_col:
/* Standardize from: for(i_col = 0;i_col < 9;i_col++) {...} */
    for (i_col = 0; i_col <= 8; i_col++) {
      int _in_i_col = (_in_j_col + 0) + 8L * i_col;
      flit = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopk:
/* Standardize from: for(k = 8;k > 0;k--) {...} */
      for (k = 7; k >= 0; k--) {
        int _in_k = 8L + 8L * k;
        int _in_idx = _in_k * 8 + _in_i_col;
        flit = orig[_in_idx] * filter[k + 8] + flit;
      }
      sol[_in_i_col] = flit;
    }
  }
}