#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  loop_up:
  for (i = 1; i < 8191; i++) {
    row_up = i - 1;
    row = i;
    row_down = i + 1;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_left:
    for (j = 1; j < 8191; j++) {
      col_up = j - 1;
      col = j;
      col_down = j + 1;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      loop_k:
      for (k = 0; k < 9; k++) {
        t += filter[k] * orig[row_up * 8192 + col_up + k - 4];
      }
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      sol[row * 8192 + col] = t;
    }
  }
}