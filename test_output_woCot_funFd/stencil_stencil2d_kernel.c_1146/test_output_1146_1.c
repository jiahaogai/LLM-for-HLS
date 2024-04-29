#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int orig_row;
  int orig_col;
  int sol_row;
  int sol_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      orig_row = 8 * i;
      orig_col = 8 * j;
      sol_row = orig_row;
      sol_col = orig_col;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = k % 3;
        k_row = k / 3;
        int orig_index = (orig_row + k_row) * 8 + orig_col + k_col;
        sol[sol_row * 8 + sol_col] += filter[k] * orig[orig_index];
      }
    }
  }
}