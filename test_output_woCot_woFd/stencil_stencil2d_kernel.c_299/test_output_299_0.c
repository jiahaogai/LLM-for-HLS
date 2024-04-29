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
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      row = i * 8;
      row_up = (i - 1) * 8;
      row_down = (i + 1) * 8;
      col = j * 8;
      col_up = (j - 1) * 8;
      col_down = (j + 1) * 8;
      t = filter[0] * orig[row + col] + filter[1] * (orig[row + col_up] + orig[row + col_down]) + filter[2] * (orig[row_up + col] + orig[row_down + col]) + filter[3] * orig[row_up + col_up] + filter[4] * orig[row_up + col_down] + filter[5] * orig[row_down + col_up] + filter[6] * orig[row_down + col_down] + filter[7] * orig[row_down + col];
      sol[row + col] = t;
    }
  }
}