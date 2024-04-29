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
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      flatten_row = i * 256;
      idx = flatten_row + j;
      val = orig[idx];
      inner:
      for (k = 0; k < 9; k++) {
        flatten_col = k - ((256 - 1) / 2);
        col = j + flatten_col;
        if (col < 0) {
          col += 256;
        }
         else {
          if (col > 255) {
            col -= 256;
          }
        }
        row = i + ((256 - 1) / 2) - flatten_col;
        if (row < 0) {
          row += 256;
        }
         else {
          if (row > 255) {
            row -= 256;
          }
        }
        val += filter[k] * orig[row * 256 + col];
      }
      sol[idx] = val;
    }
  }
}