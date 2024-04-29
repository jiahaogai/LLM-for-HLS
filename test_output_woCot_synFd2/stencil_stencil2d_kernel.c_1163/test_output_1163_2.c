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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      orig_row = i * 32 - 1;
      orig_col = j * 32 - 1;
      sol_row = (i + 1) * 32 - 1;
      sol_col = (j + 1) * 32 - 1;
      int sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        int k_row_tmp = k_row = orig_row + 1 + (k / 32);
        int k_col_tmp = k_col = orig_col + 1 + (k % 32);
        if (k_row_tmp < 0 || k_row_tmp >= 256 || k_col_tmp < 0 || k_col_tmp >= 256) {
          continue;
        }
        else {
          sum += orig[k_row * 256 + k_col] * filter[k];
        }
      }
      sol[sol_row * 256 + sol_col] = sum;
    }
  }
}