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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      orig_row = i - 4;
      orig_col = j - 4;
      sol_row = i;
      sol_col = j;
      k_col = 0;
      
#pragma ACCEL PARALLEL reduction=sol_col FACTOR=auto{1}
      inner:
      for (k_row = 0; k_row < 9; k_row++) {
        k = k_row * 8 + k_col;
        if ((((orig_row + k_row) >= 0) && ((orig_row + k_row) < 8)) && (((orig_col + k_col) >= 0) && ((orig_col + k_col) < 8))) {
          sol[sol_row * 8 + sol_col] += orig[orig_row * 8 + orig_col] * filter[k];
        }
        k_col++;
      }
    }
  }
}