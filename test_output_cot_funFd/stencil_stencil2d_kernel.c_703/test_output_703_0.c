#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int orig_row;
  int orig_col;
  int sol_row;
  int sol_col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      orig_row = i * 256;
      sol_row = i * 256;
      
      inner:
      for (k_col = 0; k_col < 9; k_col++) {
        orig_col = k_col + orig_row;
        sol_col = k_col + sol_row;
        filter[k_col] = orig[orig_col];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_1:
      for (j_col = 0; j_col < 9; j_col++) {
        sol[sol_col] = 0;
        inner_2:
        for (i_col = 0; i_col < 9; i_col++) {
          sol[sol_col] += filter[i_col] * filter[j_col * 9 + i_col];
        }
      }
    }
  }
}