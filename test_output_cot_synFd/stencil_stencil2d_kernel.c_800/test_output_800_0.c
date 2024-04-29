#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int reset_i;
  int reset_j;
  
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
      sol[i * 256 + j] = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = k % 3;
        reset_i = i + (-1 + k_col);
        reset_j = j + (-1 + (k - k_col));
        sol[i * 256 + j] += filter[k] * orig[reset_i * 256 + reset_j];
      }
    }
  }
}