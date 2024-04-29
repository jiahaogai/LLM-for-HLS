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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    row = i & 7;
    row_up = (row - 1 + 8) % 8;
    row_down = (row + 1) % 8;
    col = i & 511;
    col_up = (col - 1 + 512) % 512;
    col_down = (col + 1) % 512;
    t = 0;
    inner:
    for (j = 0; j < 9; j++) {
      t += filter[j] * orig[i + ((j - 4) % 8) * 512 + ((j - 4) / 8) * 8192];
    }
    sol[i] = t;
  }
}