#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int min_row;
  int max_row;
  int min_col;
  int max_col;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 33; i++) {
      t = 0;
      min_row = j - 1;
      if (min_row < 0) {
        min_row = 0;
      }
      max_row = j + 1;
      if (max_row > 33 - 1) {
        max_row = 33 - 1;
      }
      min_col = i - 1;
      if (min_col < 0) {
        min_col = 0;
      }
      max_col = i + 1;
      if (max_col > 33 - 1) {
        max_col = 33 - 1;
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      looprow:
      for (row = min_row; row <= max_row; row++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loopcol:
        for (col = min_col; col <= max_col; col++) {
          t += orig[row * 32 + col] * filter[((max_col - col) + 1) + ((max_row - row) + 1) * 3];
        }
      }
      sol[j * 32 + i] = t;
    }
  }
}