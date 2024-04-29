#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int orig_row_start;
  int orig_row_end;
  int orig_col_start;
  int orig_col_end;
  int sol_row_start;
  int sol_row_end;
  int sol_col_start;
  int sol_col_end;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  orig_row_start = 1;
  orig_row_end = 8190;
  orig_col_start = 1;
  orig_col_end = 8190;
  sol_row_start = 1;
  sol_row_end = 8190;
  sol_col_start = 1;
  sol_col_end = 8190;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_row:
  for (i = orig_row_start; i < orig_row_end + 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loop_col:
    for (j = orig_col_start; j < orig_col_end + 1; j++) {
      sum = 0;
      loop_filter:
      for (k = 0; k < 9; k++) {
        int orig_idx = i + (-1 + k) / 8192 * (8191 - 1);
        int orig_col = j + (-1 + k) % 8192;
        sum += filter[k] * orig[orig_idx * 8192 + orig_col];
      }
      sol[i * 8192 + j] = sum;
    }
  }
}