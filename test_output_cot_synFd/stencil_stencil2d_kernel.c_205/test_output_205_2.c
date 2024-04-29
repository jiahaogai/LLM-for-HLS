Code: #pragma ACCEL kernel

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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 1; j < 8190; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopi:
    for (i = 1; i < 8188; i++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopk:
      for (k = -4; k < 5; k++) {
        row_up = (j - 1 + 8190) % 8190;
        row_down = (j + 1) % 8190;
        col_up = (i - 1 + 8188) % 8188;
        col_down = (i + 1) % 8188;
        row = (j + 8190) % 8190;
        col = (i + 8188) % 8188;
        t += filter[k + 4] * orig[row_up * 8188 + col_up];
        t += filter[k + 4] * orig[row * 8188 + col_down];
        t += filter[k + 4] * orig[row_down * 8188 + col_up];
        t += filter[k + 4] * orig[row_down * 8188 + col];
      }
      sol[row * 8188 + col] = t;
    }
  }
}