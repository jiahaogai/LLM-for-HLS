#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64 + 2; j++) {
      row = i - 1;
      col = j - 1;
      flit = 0;
      
#pragma ACCEL PARALLEL reduction = flit FACTOR=auto{16}
      inner:
      for (k = 0; k < 9; k++) {
        if (row + ((int )k / 3) >= 0 && row + ((int )k / 3) < 128 && col + ((k % 3)) >= 0 && col + ((k % 3)) < 64) {
          flit += filter[k] * orig[row + ((int )k / 3)][col + ((k % 3)]];
        }
      }
      sol[i][j] = flit;
    }
  }
}