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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 8191; i++) {
      t = 0;
      row_up = (8192 + j - 1) % 8192;
      row_down = (j + 1) % 8192;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{2}
      loopk:
      for (k = -1; k <= 1; k++) {
        row = (row_up + k + 8192) % 8192;
        col_left = (i - 1) % 8192;
        col_right = (i + 1) % 8192;
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{2}
        loopl:
        for (l = -1; l <= 1; l++) {
          col = (col_left + l + 8192) % 8192;
          t += filter[k + 1][l + 1] * orig[row * 8192 + col];
        }
      }
      sol[j * 8192 + i] = t;
    }
  }
}