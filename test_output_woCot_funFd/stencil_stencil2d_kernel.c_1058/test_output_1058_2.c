#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_left;
  int col_right;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  loop:
/* Standardize from: for(i = 0; i < 8; i++) {...} */
  standardize:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    inner_loop:
    for (j = 0; j < 8; j++) {
      row = i * 8;
      row_up = (i - 1) * 8;
      row_down = (i + 1) * 8;
      col = j * 8;
      col_left = j * 8 - 1;
      col_right = j * 8 + 1;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      sum_loop:
      for (t = 0; t < 9; t++) {
        if ((((row - 1) < 0) || ((col - 1) < 0)) || (((row_up + t) > 8183) || ((col_left + t) > 8183))) {
          continue;
        }
        else {
          t = orig[((row_up + t)) * 8 + (col_left + t)] + orig[((row_up + t)) * 8 + col + t] + orig[((row_up + t)) * 8 + (col_right + t)] + orig[((row + t)) * 8 + (col_left + t)] + orig[((row + t)) * 8 + col + t] + orig[((row + t)) * 8 + (col_right + t)] + orig[(row_down + t) * 8 + (col_left + t)] + orig[(row_down + t) * 8 + col + t] + orig[(row_down + t) * 8 + (col_right + t)];
        }
      }
      sol[row * 8 + col] = t;
    }
  }
}