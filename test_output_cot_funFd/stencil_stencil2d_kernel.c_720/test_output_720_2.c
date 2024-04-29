#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{126}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int orig_row_start;
  int orig_row_end;
  int orig_col_start;
  int orig_col_end;
  int sol_row_start;
  int sol_row_end;
  int sol_col_start;
  int sol_col_end;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  int middle;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  int r;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  int c;
  middle = 400 + 2;
  r = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  while (r < 400 - 1) {
    c = 0;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    while (c < 400 - 1) {
      tmp = 0;
      orig_row_start = r - 1;
      if (orig_row_start < 0) {
        orig_row_start = 0;
      }
      orig_row_end = r + 2;
      if (orig_row_end > 400 - 1) {
        orig_row_end = 400 - 1;
      }
      orig_col_start = c - 1;
      if (orig_col_start < 0) {
        orig_col_start = 0;
      }
      orig_col_end = c + 2;
      if (orig_col_end > 400 - 1) {
        orig_col_end = 400 - 1;
      }
      sol_row_start = r - 1;
      if (sol_row_start < 0) {
        sol_row_start = 0;
      }
      sol_row_end = r + 2;
      if (sol_row_end > 400 - 1) {
        sol_row_end = 400 - 1;
      }
      sol_col_start = c - 1;
      if (sol_col_start < 0) {
        sol_col_start = 0;
      }
      sol_col_end = c + 2;
      if (sol_col_end > 400 - 1) {
        sol_col_end = 400 - 1;
      }
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      int filter_row_start;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      int filter_row_end;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      int filter_col_start;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      int filter_col_end;
      filter_row_start = 0;
      filter_row_end = 0 + 2;
      filter_col_start = 0;
      filter_col_end = 0 + 2;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      int filter_idx;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      int flatten_idx;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{2}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      int tmp_1;
      int tmp_2;
      int tmp_3;
      flatten_idx = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      int orig_idx;
      orig_idx = 0 + (orig_row_start * 400) + orig_col_start;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      int filter_idx_0;
      filter_idx_0 = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{8}
      int filter_idx_1;
      filter_idx_1 = 1;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      int filter_idx_2;
      filter_idx_2 = 2;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      int sol_idx;
      sol_idx = 0 + (sol_row_start * 400) + sol_col_start;
      for (filter_idx = filter_row_start; filter_idx < filter_row_end; filter_idx++) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        for (filter_idx_0 = filter_col_start; filter_idx_0 < filter_col_end; filter_idx_0++) {
          tmp_1 = filter[filter_idx * 3 + 0];
          tmp_2 = filter[filter_idx * 3 + 1];
          tmp_3 = filter[filter_idx * 3 + 2];
          tmp += orig[flatten_idx + tmp_1] * tmp_2 * tmp_3;
          flatten_idx += 1;
        }
      }
      sol[sol_idx] = tmp;
      c++;
    }
    r++;
  }
}