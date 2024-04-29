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
  int col_up;
  int col_down;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{7}
    middle:
    for (j = 0; j < 8; j++) {
      row = i * 8;
      row_up = (i - 1) * 8;
      row_down = (i + 1) * 8;
      col = j * 8;
      col_up = (j - 1) * 8;
      col_down = (j + 1) * 8;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{14}
      inner:
      for (t = 0; t < 9; t++) {
        if (t != 4) {
          if (t == 0) {
            t = orig[row_up + col_up];
          }
          
#pragma ACCEL PIPELINE auto{off}
          if (t == 1) {
            t = orig[row_up + col];
          }
          
#pragma ACCEL PIPELINE auto{off}
          if (t == 2) {
            t = orig[row_up + col_down];
          }
          
#pragma ACCEL PIPELINE auto{off}
          if (t == 3) {
            t = orig[row_down + col_down];
          }
          
#pragma ACCEL PIPELINE auto{off}
          if (t == 4) {
            t = orig[row + col];
          }
          
#pragma ACCEL PIPELINE auto{off}
          if (t == 5) {
            t = orig[row_down + col];
          }
          
#pragma ACCEL PIPELINE auto{off}
          if (t == 6) {
            t = orig[row_down + col_up];
          }
          
#pragma ACCEL PIPELINE auto{off}
          if (t == 7) {
            t = orig[row_up + col_up];
          }
        }
      }
      sol[row + col] = t;
    }
  }
}