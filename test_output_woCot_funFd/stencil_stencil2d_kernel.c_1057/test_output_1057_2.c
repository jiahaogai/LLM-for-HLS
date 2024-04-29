Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int fidx;
  int orig_row_idx;
  int sol_row_idx;
  int upper_row_idx;
  int lower_row_idx;
  int orig_col_idx;
  int sol_col_idx;
  int left_col_idx;
  int right_col_idx;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  loopj:
  for (j = 1; j < 33 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
    for (k = 1; k < 33 - 1; k++) {
      orig_row_idx = (j - 1) * 32 + 1;
      sol_row_idx = (j - 1) * 32;
      upper_row_idx = orig_row_idx - 1;
      lower_row_idx = orig_row_idx + 1;
      orig_col_idx = (k - 1) * 32 + 1;
      sol_col_idx = (k - 1) * 32;
      left_col_idx = orig_col_idx - 1;
      right_col_idx = orig_col_idx + 1;
      idx = sol_row_idx * 32 + sol_col_idx;
      fidx = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
      for (i = 0; i < 9; i++) {
        fidx += filter[i] * orig[upper_row_idx + i] * orig[left_col_idx + i] * orig[right_col_idx + i] * orig[lower_row_idx + i];
      }
      sol[idx] = fidx;
    }
  }
}