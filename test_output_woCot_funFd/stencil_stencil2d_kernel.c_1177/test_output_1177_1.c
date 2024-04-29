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
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopi:
    for (i = 1; i < 8191; i++) {
      t = 0;
      row_up = (8191 + j - 1) % 8191;
      row_down = (j + 1) % 8191;
      
#pragma ACCEL PARALLEL FACTOR=auto{9}
      loopk:
      for (k = -1; k <= 1; k++) {
        row = (row_up + k + 8191) % 8191;
        col_up = (8191 + i - 1) % 8191;
        col_down = (i + 1) % 8191;
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        loopt:
        for (t = 0; t < 9; t++) {
          col = (col_up + (t - 4) + 8191) % 8191;
          t = filter[t] * orig[row * 8192 + col];
        }
      }
      sol[j * 8192 + i] = t;
    }
  }
}