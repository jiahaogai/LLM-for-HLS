#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int orig_row;
  int orig_col;
  int sol_row;
  int sol_col;
  int filter_row;
  int filter_col;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj_col:
/* Standardize from: for(j_col = 1; j_col < 9; j_col++) {...} */
  for (j_col = 1; j_col < 9; j_col++) {
    int _in_j_col = 0 + 8 * (j_col - 1);
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi_col:
/* Standardize from: for(i_col = 1; i_col < 9; i_col++) {...} */
    for (i_col = 1; i_col < 9; i_col++) {
      int _in_i_col = _in_j_col + i_col;
      sol_col = _in_i_col;
      orig_col = _in_i_col;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopfilter_row:
/* Standardize from: for(filter_row = 0; filter_row < 9; filter_row++) {...} */
      for (filter_row = 0; filter_row < 9; filter_row++) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        loopfilter_col:
/* Standardize from: for(filter_col = 0; filter_col < 9; filter_col++) {...} */
        for (filter_col = 0; filter_col < 9; filter_col++) {
          int _in_filter_col = 8 * filter_col;
          int _in_filter_row = 8 * filter_row;
          orig_row = _in_filter_row + _in_i_col;
          
#pragma ACCEL REORDER
          sol[sol_col] = ((0 + filter[filter_row * 9 + filter_col]) * orig[orig_row * 8192 + orig_col]) + sol[sol_col];
        }
      }
    }
  }
}