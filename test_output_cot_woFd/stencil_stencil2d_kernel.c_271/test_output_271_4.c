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
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      int filter_elem = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (filter_elem = 0; filter_elem < 9; filter_elem++) {
        int index = filter_elem - 4;
        int row_index = i + index / 8;
        int col_index = j + index % 8;
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        if ((((row_index >= 0) && (row_index < 256)) && ((col_index >= 0) && (col_index < 256))) && (!((row_index == 0) && (col_index == 0)))) {
          t += orig[row_index * 256 + col_index] * filter[filter_elem];
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}