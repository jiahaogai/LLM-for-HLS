#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int col;
  int temp_orig;
  int temp_sol;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 256; j++) {
      temp_orig = orig[i * 256 + j];
      temp_sol = 0;
      
#pragma ACCEL PARALLEL reduction = temp_sol FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = k % 3;
        row = i - 1 + k_col;
        row = row < 0 ? 0 : row > 255 ? 255 : row;
        col = j - 1 + (k - k_col);
        col = col < 0 ? 0 : col > 255 ? 255 : col;
        temp_sol += filter[k] * orig[row * 256 + col];
      }
      sol[i * 256 + j] = temp_sol;
    }
  }
}