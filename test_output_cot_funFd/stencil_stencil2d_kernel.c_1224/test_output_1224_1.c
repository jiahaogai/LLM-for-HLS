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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      sol_row = ((i + 8) < 256 ? (i + 8) : 256) - 1;
      sol_col = ((j + 8) < 256 ? (j + 8) : 256) - 1;
      orig_row = i - 1;
      orig_col = j - 1;
      sol[sol_row * 256 + sol_col] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        filter_row = ((4 + ((k / 3) * 8)) < 256 ? (4 + ((k / 3) * 8)) : 256) - 1;
        filter_col = ((4 + ((k % 3) * 8)) < 256 ? (4 + ((k % 3) * 8)) : 256) - 1;
        sol[sol_row * 256 + sol_col] += orig[orig_row * 256 + orig_col] * filter[filter_row * 9 + filter_col];
      }
    }
  }
}