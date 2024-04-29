#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flatten_row;
  int flatten_col;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{18}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      s = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        row = i + ((k / 3) - 1);
        col = j + ((k % 3) - 1);
        if (row < 0 || 255 < row) {
          row = 0 > row ? 0 : 255;
        }
        if (col < 0 || 255 < col) {
          col = 0 > col ? 0 : 255;
        }
        idx = row * 256 + col;
        s += ((double )filter[k]) * orig[idx];
      }
      flatten_row = i / 32;
      flatten_col = j / 32;
      idx = flatten_row * 32 + flatten_col;
      sol[idx] = s;
    }
  }
}