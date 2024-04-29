#pragma ACCEL kernel

void stencil(out int sol[8192],in int orig[8192],in int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  int orig_row_idx;
  int orig_col_idx;
  int sol_row_idx;
  int sol_col_idx;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  int row_up = -1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  int row_down = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  int col_left = -1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  int col_right = 1;
  int flatten_orig[9];
  
#pragma ACCEL PIPELINE auto{off}
  int flatten_sol[9];
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    orig_row_idx = i >> 11;
    orig_col_idx = i & 0x3ff;
    sol_row_idx = i >> 9;
    sol_col_idx = i & 0x1ff;
    
#pragma ACCEL PIPELINE auto{off}
    flatten_orig[0] = orig[i];
    
#pragma ACCEL PIPELINE auto{off}
    flatten_orig[1] = orig[i + 1];
    
#pragma ACCEL PIPELINE auto{off}
    flatten_orig[2] = orig[i + 2];
    
#pragma ACCEL PIPELINE auto{off}
    flatten_orig[3] = orig[i + 8192];
    
#pragma ACCEL PIPELINE auto{off}
    flatten_orig[4] = orig[i + 8193];
    
#pragma ACCEL PIPELINE auto{off}
    flatten_orig[5] = orig[i + 8194];
    
#pragma ACCEL PIPELINE auto{off}
    flatten_orig[6] = orig[i + 2 * 8192];
    
#pragma ACCEL PIPELINE auto{off}
    flatten_orig[7] = orig[i + 2 * 8192 + 1];
    
#pragma ACCEL PIPELINE auto{off}
    flatten_orig[8] = orig[i + 2 * 8192 + 2];
    
#pragma ACCEL ARRAY FACTOR=auto{1}
    for (j = 0; j < 9; j++) {
      result = ((filter[j]) * (flatten_orig[j]));
      flatten_sol[j] = result;
    }
    
#pragma ACCEL PIPELINE auto{off}
    sol[i] = flatten_sol[0];
    
#pragma ACCEL PIPELINE auto{off}
    sol[i + 1] = flatten_sol[1];
    
#pragma ACCEL PIPELINE auto{off}
    sol[i + 2] = flatten_sol[2];
    
#pragma ACCEL PIPELINE auto{off}
    sol[i + 8192] = flatten_sol[3];
    
#pragma ACCEL PIPELINE auto{off}
    sol[i + 8193] = flatten_sol[4];
    
#pragma ACCEL PIPELINE auto{off}
    sol[i + 8194] = flatten