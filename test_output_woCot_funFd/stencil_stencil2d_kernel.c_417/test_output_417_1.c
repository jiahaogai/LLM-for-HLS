#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int orig_row_idx;
  int orig_col_idx;
  int sol_row_idx;
  int sol_col_idx;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 256; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        orig_row_idx = i + (-1 + k);
        orig_col_idx = j + (-1 + k);
        sum += filter[k] * orig[orig_row_idx * 256 + orig_col_idx];
      }
      sol_row_idx = i;
      sol_col_idx = j;
      sol[sol_row_idx * 256 + sol_col_idx] = sum;
    }
  }
}