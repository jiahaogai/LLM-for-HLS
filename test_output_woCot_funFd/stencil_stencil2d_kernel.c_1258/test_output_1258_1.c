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
  loopj:
  for (j = 1; j < 8188; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopi:
    for (i = 1; i < 8188; i++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{9}
      loopk:
      for (k = -4; k < 5; k++) {
        row_up = (8188 + j - 4) % 8188;
        row_down = (8188 + j + 4) % 8188;
        col_up = (8188 + i - 4) % 8188;
        col_down = (8188 + i + 4) % 8188;
        row = j % 8188;
        col = i % 8188;
        t += filter[k + 4] * orig[col_up * 8192 + row_up]
          + filter[k + 4] * orig[col_down * 8192 + row_down];
      }
      sol[i * 8192 + j] = t;
    }
  }
}