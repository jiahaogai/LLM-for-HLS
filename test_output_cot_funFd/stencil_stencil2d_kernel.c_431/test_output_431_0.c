#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 256; j++) {
      flit = 0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = k % 9;
        row = i - 4 + (k - k_col);
        col = j - 4 + k_col;
        if (row < 0 || 256 <= row || col < 0 || 256 <= col) {
          flit = 0;
        }
         else {
          flit += orig[row * 256 + col] * filter[k];
        }
      }
      sol[i * 256 + j] = flit;
    }
  }
}