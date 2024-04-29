#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      k_col = 0;
      
      inner:
      while (k_col < 9) {
        k = k_col + i - 4;
        int bound_up = 256 - 1;
        int bound_down = 0;
        int bound_left = 256 - 1;
        int bound_right = 0;
        if (k > bound_up) {
          k = bound_up;
        }
        if (k < bound_down) {
          k = bound_down;
        }
        if (j > bound_right) {
          j = bound_right;
        }
        if (j < bound_left) {
          j = bound_left;
        }
        result = orig[k * 256 + j] * filter[k_col];
        sol[i * 256 + j] = result;
        k_col++;
      }
    }
  }
}