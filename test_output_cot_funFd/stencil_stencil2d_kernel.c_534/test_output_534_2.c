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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      temp_orig = 0;
      temp_sol = 0;
      
#pragma ACCEL PARALLEL reduction=temp_orig FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = k % 3;
        row = i - 1 + k_col;
        col = j - 1 + (k - k_col);
        if (row < 0 || row > 255 || col < 0 || col > 255) {
          temp_orig = 0;
        }
         else {
          temp_orig = orig[row * 256 + col];
        }
        filter[k] = temp_orig;
      }
      inner_sol:
      for (k = 0; k < 9; k++) {
        temp_sol += filter[k] * sol[(((k / 3) * 256) + i) * 256 + j];
      }
      temp_sol /= 9;
      orig[i * 256 + j] = temp_sol;
    }
  }
}