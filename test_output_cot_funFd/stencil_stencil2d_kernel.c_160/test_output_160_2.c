#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row_up;
  int row_down;
  int row;
  int col;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_row_up:
  for (row_up = 1; row_up < 8; row_up++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loop_row_down:
    for (row_down = -1; row_down > -8; row_down--) {
      row = row_up + row_down;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_col:
      for (col = 1; col < 8; col++) {
        i = row * 8 + col;
        sum = 0.0;
        loop_k_col:
        for (k_col = 0; k_col < 9; k_col++) {
          k = k_col + col - 1;
          sum += filter[k_col] * orig[i - k];
        }
        sol[i] = sum;
      }
    }
  }
}