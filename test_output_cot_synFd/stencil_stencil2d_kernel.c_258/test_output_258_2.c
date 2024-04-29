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
  int col_left;
  int col_right;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  loop_j:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    loop_i:
    for (i = 1; i < 8191; i++) {
      t = 0;
      int loop_k_bound = 9;
      int loop_k_step = 1;
      loop_k:
      for (k = 0; k < 9; k++) {
        row_up = (j - 1 + 8191) % 8192;
        row_down = (j + 1) % 8192;
        col_left = (i - 1 + 8191) % 8192;
        col_right = (i + 1) % 8192;
        row = (j + 8191) % 8192;
        t += filter[k] * orig[row_up * 8192 + col_left] + filter[k] * orig[row_up * 8192 + i] + filter[k] * orig[row_up * 8192 + col_right] + filter[k] * orig[row * 8192 + col_left] + filter[k] * orig[row * 8192 + col_right] + filter[k] * orig[row_down * 8192 + col_left] + filter[k] * orig[row_down * 8192 + i] + filter[k] * orig[row_down * 8192 + col_right];
      }
      sol[row * 8192 + i] = t;
    }
  }
}