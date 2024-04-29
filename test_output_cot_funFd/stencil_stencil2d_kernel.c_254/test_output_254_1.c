#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      row_up = (i - 1 + 256) % 256;
      row_down = (i + 1) % 256;
      col_up = (j - 1 + 256) % 256;
      col_down = (j + 1) % 256;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = (k - 1 + 9) % 9;
        row = (col_up + k_col) % 256;
        col = (row_up + k_col) % 256;
        t += orig[col * 256 + row] * filter[k];
      }
      sol[i * 256 + j] = t;
    }
  }
}