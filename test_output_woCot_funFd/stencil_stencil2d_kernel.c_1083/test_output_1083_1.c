Code: 
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64; j++) {
      col = -1;
      int k_row_tmp = -1;
      
#pragma ACCEL PARALLEL reduction = sol FACTOR=auto{1}
      inner:
      for (k_row = 0; k_row < 3; k_row++) {
        k_row_tmp += 1;
        row = i - 1 + k_row_tmp;
        int k_col_tmp = -1;
        
#pragma ACCEL PARALLEL reduction = col FACTOR=auto{1}
        inner_1:
        for (k_col = 0; k_col < 3; k_col++) {
          k_col_tmp += 1;
          col += filter[k_col + 3 * k_row] * orig[row * 64 + j + k_col_tmp];
        }
      }
      sol[i * 64 + j] = col;
    }
  }
}