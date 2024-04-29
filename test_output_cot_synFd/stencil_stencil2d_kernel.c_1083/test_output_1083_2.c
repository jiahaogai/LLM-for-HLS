#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int offset;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64; j++) {
      offset = i * 64 + j;
      sol[offset] = 0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = k % 3;
        k_row = k / 3;
        int x_col = j + k_col - 1;
        int x_row = i + k_row - 1;
        if (x_col < 0 || x_col > 63 || x_row < 0 || x_row > 127) {
          continue;
        }
        sol[offset] += filter[k] * orig[x_row * 64 + x_col];
      }
    }
  }
}