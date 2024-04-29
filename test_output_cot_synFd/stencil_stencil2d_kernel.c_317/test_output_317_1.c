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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  loopj:
  for (j = 1; j < 8191; j++) {
    row_up = 8191 + j - 1;
    row = 8191 + j;
    row_down = 8191 + j + 1;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 8191; i++) {
      col_up = 8191 * row_up + i - 1;
      col = 8191 * row + i;
      col_down = 8191 * row_down + i - 1;
      t = filter[4] * orig[col] + filter[0] * orig[col_up] + filter[1] * orig[col_down] + filter[2] * orig[col_up + 1] + filter[3] * orig[col_down + 1];
      sol[col] = t;
    }
  }
}