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
  int r_col_min;
  int r_col_max;
  int c_col_min;
  int c_col_max;
  int k1;
  int k2;
  int temp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loopr:
/* Standardize from: for(r = 0; r < 128 + 2; r++) {...} */
  for (r = 0; r <= 128 + 1; r++) {
    int _in_r = r - 1;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopc:
    for (c = 0; c <= 128 + 1; c++) {
      int _in_c = c - 1;
      r_col_min = r - 1 < 0 ? 0 : r - 1;
      r_col_max = r + 2 > 129 ? 129 : r + 2;
      c_col_min = c - 1 < 0 ? 0 : c - 1;
      c_col_max = c + 2 > 129 ? 129 : c + 2;
      temp = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk1:
      for (k1 = r_col_min; k1 < r_col_max; k1++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loopk2:
        for (k2 = c_col_min; k2 < c_col_max; k2++) {
          int _in_k = k1 * 128 + k2;
          k = _in_k;
          i_col = k1;
          j_col = k2;
          temp += orig[k] * filter[k1 * 3 + k2];
        }
      }
      sol[i_col * 128 + j_col] = temp;
    }
  }
}