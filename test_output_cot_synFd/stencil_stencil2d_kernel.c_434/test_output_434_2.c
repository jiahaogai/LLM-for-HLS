#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 8; j < 8184; j += 8) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
      inner:
      for (k = 0; k < 9; k++) {
        row_up = i - 1;
        row_down = i + 1;
        col_up = j - 1;
        col_down = j + 1;
        if (row_up < 0) {
          row_up = 0;
        }
        if (row_down > 8183) {
          row_down = 8183;
        }
        if (col_up < 0) {
          col_up = 0;
        }
        if (col_down > 8183) {
          col_down = 8183;
        }
        row = (row_up + row_down) / 2;
        col = (col_up + col_down) / 2;
        t += filter[k] * orig[row * 8192 + col];
      }
      sol[i * 8192 + j] = t;
    }
  }
}