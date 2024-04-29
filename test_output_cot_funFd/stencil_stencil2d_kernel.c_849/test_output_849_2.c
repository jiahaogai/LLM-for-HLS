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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 8; j < 992; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopi:
    for (i = 8; i < 992; i++) {
      t = 0;
      row_up = (8 > j) ? 8 : j;
      row_down = (992 < j + 2) ? 992 : j + 2;
      row = row_down - row_up + 1;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopk:
      for (k = row_up; k <= row_down - 1; k++) {
        col_left = (8 > i) ? 8 : i;
        col_right = (992 < i + 2) ? 992 : i + 2;
        col = col_right - col_left + 1;
        t += orig[i + (k * 9)] * filter[col];
      }
      sol[i + (j * 9)] = t;
    }
  }
}