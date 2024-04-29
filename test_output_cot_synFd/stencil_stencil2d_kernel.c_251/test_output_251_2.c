#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int flatten_size;
  int elem_count;
  int row_up;
  int row_down;
  int col_left;
  int col_right;
  int idx;
  int flatten_idx;
  int elem_val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  flatten_size = 9 * 9;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{31}
  elem_count = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loop_up:
  for (i = 8; i < 8192 + 8; i += 8) {
    
#pragma ACCEL PARALLEL reduction = sol FACTOR=auto{2}
    loop_col:
    for (j = 8; j < 8192 + 8; j += 8) {
      row_up = i - 8;
      row_down = i + 8;
      col_left = j - 8;
      col_right = j + 8;
      idx = 4 * (i / 64) + (j / 64);
      flatten_idx = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_k:
      for (k = 0; k < 9; k++) {
        
#pragma ACCEL PARALLEL reduction = flatten_idx FACTOR=auto{2}
        loop_k_col:
        for (k_col = 0; k_col < 9; k_col++) {
          i_col = k_col + row_up;
          j_col = k_col + col_left;
          if (((i_col >= 0) && (i_col < 8192)) && ((j_col >= 0) && (j_col < 8192))) {
            elem_val = orig[i_col * 8192 + j_col];
          }
           else {
            elem_val = 0;
          }
          sol[idx * 9 + k_col] += filter[k * 9 + k_col] * elem_val;
        }
        flatten_idx += 8;
      }
      elem_count++;
    }
  }
}