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
  int filter_row;
  int filter_col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
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
      for (k = 0; k < 9; k++) {
        orig_col = ((k + 1) * 32) - 1;
        filter_col = k * 32;
        sol_col = filter_col;
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
	middle_inner:
	for (j_col = 0; j_col < 32; j_col++) {
          int orig_index = orig_row + orig_col;
          int sol_index = sol_row + sol_col;
          sol[sol_index] += orig[orig_index] * filter[k];
          sol_col += 256;
        }
      }
    }
  }
}