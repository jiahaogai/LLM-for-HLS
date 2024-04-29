#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  int flit_row;
  int flit_col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      inner:
      for (row = -1; row <= 1; row++) {
        flit_row = row + i;
        if (flit_row < 0 || flit_row > 255) {
          continue;
        }
        inner_inner:
        for (col = -1; col <= 1; col++) {
          flit_col = col + j;
          if (flit_col < 0 || flit_col > 255) {
            continue;
          }
          t += orig[flit_row * 256 + flit_col] * filter[row + 1 * col + 1];
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}