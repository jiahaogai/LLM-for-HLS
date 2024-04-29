#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 64 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      int orig_idx = 8192 * (j - 1) + (k_col - 4);
      double orig_val = orig[orig_idx];
      loopk_row:
      for (k_row = 0; k_row < 9; k_row++) {
        int filter_idx = 9 * (k_row - 4) + (k_col - 4);
        double filter_val = filter[filter_idx];
        int sol_idx = 8192 * (j - 1) + (k_row - 1);
        sol[sol_idx] += orig_val * filter_val;
      }
    }
  }
}