#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 64; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = j + ((k % 3) - 1);
        k_row = i + ((k / 3) - 1);
        if ((((0 <= k_col) && (k_col < 64))) && (((0 <= k_row) && (k_row < 64)))) {
          sum += filter[k] * orig[k_row * 64 + k_col];
        }
      }
      sol[i * 64 + j] = sum;
    }
  }
}