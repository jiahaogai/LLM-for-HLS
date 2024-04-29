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
  int col_left;
  int col_right;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loop_j:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_i:
    for (i = 1; i < 8191; i++) {
      t = 0;
      row_up = (8192 + j - 1) % 8192;
      row_down = j;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{2}
      loop_col_up:
      for (col = (i - 1 + 8192) % 8192; col < (i + 2) % 8192; col++) {
        t += orig[col] * filter[col - (i - 1 + 8192) % 8192];
      }
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{2}
      loop_col_down:
      for (col = i; col < (i + 2) % 8192; col++) {
        t += orig[col] * filter[col - i];
      }
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{2}
      loop_col_left:
      for (col = (i - 1) % 8192 + 8192; col < (i + 2) % 8192 + 8192; col++) {
        t += orig[col] * filter[col - (i - 1) % 8192];
      }
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{2}
      loop_col_right:
      for (col = i % 8192; col < (i + 2) % 8192; col++) {
        t += orig[col] * filter[col - i % 8192];
      }
      sol[j] = t;
    }
  }
}