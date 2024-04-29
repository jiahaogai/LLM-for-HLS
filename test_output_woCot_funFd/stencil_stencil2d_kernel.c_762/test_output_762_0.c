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
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner:
      for (row = -1; row <= 1; row++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        inner_1:
        for (col = -1; col <= 1; col++) {
          row_up = (i + row);
          row_down = (i + row);
          col_left = (j + col);
          col_right = (j + col);
          if (row_up < 0) {
            row_up = 0;
          }
          if (row_down > 255) {
            row_down = 255;
          }
          if (col_left < 0) {
            col_left = 0;
          }
          if (col_right > 255) {
            col_right = 255;
          }
          filter_elem = filter[filter_idx(row,col)];
          t += orig[get_idx(row_up,col_left)] * filter_elem;
          t += orig[get_idx(row_up,col_right)] * filter_elem;
          t += orig[get_idx(row_down,col_left)] * filter_elem;
          t += orig[get_idx(row_down,col_right)] * filter_elem;
        }
      }
      sol[get_idx(i,j)] = t;
    }
  }
}