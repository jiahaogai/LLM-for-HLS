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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 8192; j++) {
      row_up = (i == 0) ? 0 : i - 1;
      row_down = (i == 8191) ? 0 : i + 1;
      col_up = (j == 0) ? 0 : j - 1;
      col_down = (j == 8191) ? 0 : j + 1;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        row = (k / 32) * 32;
        col = (k % 32) * 32;
        t += filter[k] * orig[row_up * 32 + col_up]
             * orig[row_up * 32 + col]
             * orig[row_up * 32 + col_down]
             * orig[row * 32 + col_up]
             * orig[row * 32 + col]
             * orig[row * 32 + col_down]
             * orig[row_down * 32 + col_up]
             * orig[row_down * 32 + col]
             * orig[row_down * 32 + col_down];
      }
      sol[i * 32 + j] = t;
    }
  }
}