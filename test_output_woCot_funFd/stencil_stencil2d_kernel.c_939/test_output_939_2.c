#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int col;
  int flatten_row;
  int flatten_col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loopj:
  for (j = 0; j < 32; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopk_col:
    for (k_col = 0; k_col < 32; k_col++) {
      int k_col_idx = -1;
      
#pragma ACCEL PARALLEL reduction = sol FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        if (k == 4) {
          k_col_idx = k_col;
        }
        int orig_idx = ((((((j + k) * 32) + k_col) * 32) + 1) - 1);
        int sol_idx = ((((((j + 4 - k) * 32) + k_col_idx) * 32) + 1) - 1);
        sol[sol_idx] += filter[k] * orig[orig_idx];
      }
    }
  }
}