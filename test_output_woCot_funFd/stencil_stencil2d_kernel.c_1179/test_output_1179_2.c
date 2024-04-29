- The function has a total of 3 loops at different loop nesting levels.
- Flat and auto tiling and parallelization were enabled for all 3 loops.
- Pipelining was enabled for the inner loop with flatten option and for the middle loop with off option.

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int orig_row;
  int orig_col;
  int sol_row;
  int sol_col;
  int t;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      orig_row = i * 8;
      orig_col = j * 8;
      sol_row = i * 8;
      sol_col = j * 8;
      
#pragma ACCEL PARALLEL reduction = sol FACTOR=auto{1}
      inner:
      for (k = 0; k < 8; k++) {
        
#pragma ACCEL PARALLEL reduction = t FACTOR=auto{1}
	inner_1:
	for (k_col = 0; k_col < 8; k_col++) {
          int orig_index = orig_row + k + ((k_col ) << 3);
          t += filter[k] * orig[orig_index];
        }
	sol[sol_row + k] = t;
        t = 0;
      }
    }
  }
}