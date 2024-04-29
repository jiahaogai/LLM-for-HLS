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
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 128 + 2; j++) {
      row_up = MIN(i, 128);
      row_down = MAX(i, 128);
      col_left = MIN(j, 128);
      col_right = MAX(j, 128);
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (row = row_up; row <= row_down; row++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
        inner_1:
        for (col = col_left; col <= col_right; col++) {
          t += orig[row * 128 + col] * filter[col - j + 4];
        }
      }
      sol[i * 128 + j] = t;
    }
  }
}