#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_left;
  int col_right;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 8192; i++) {
    row = i * 64;
    row_up = row - 64;
    row_down = row + 64;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    inner:
    for (j = 0; j < 64; j++) {
      col = j * 8;
      col_left = col - 8;
      col_right = col + 8;
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      middle:
      for (k = 0; k < 9; k++) {
        if ((((row_up + k) ^ 4095) >> 6) == ((row ^ 4095) >> 6)) {
          if ((((col_left + k) ^ 4095) >> 3) == ((col ^ 4095) >> 3)) {
            if (k == 4) {
              tmp += orig[row_up + k] ;
            }
          }
        }
      }
      sol[row + j] = tmp;
    }
  }
}