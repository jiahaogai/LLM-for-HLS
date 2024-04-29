#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flatten_row;
  int flatten_col;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    inner:
    for (j = 0; j < 256; j++) {
      s = 0.0;
      int filter_idx;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      filter_idx = 0;
      inner_filter:
      for (k = -4; k <= 4; k++) {
        int row_idx;
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        row_idx = i + k;
        if (row_idx < 0 || 256 <= row_idx) {
          row_idx = (row_idx < 0 ? -row_idx : (256 - row_idx));
          row_idx = 256 - row_idx;
        }
        int col_idx;
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        col_idx = j + filter_idx;
        if (col_idx < 0 || 256 <= col_idx) {
          col_idx = (col_idx < 0 ? -col_idx : (256 - col_idx));
          col_idx = 256 - col_idx;
        }
        idx = row_idx * 256 + col_idx;
        s += ((double )filter[filter_idx]) * ((double )orig[idx]);
        filter_idx++;
      }
      flatten_row = i * 32 + j / 32;
      flatten_col = j % 32;
      sol[flatten_row * 32 + flatten_col] = s;
    }
  }
}