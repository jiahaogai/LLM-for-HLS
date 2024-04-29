#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int sol_row;
  int orig_row;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{18}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      sol_row = i * 256 + j;
      orig_row = i * 16 + j % 16;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = j * 16 + k % 16;
        sol[sol_row] += filter[k] * orig[orig_row * 256 + k_col];
      }
    }
  }
}