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
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((j + 4) - 5 + ((k % 3) - 1));
        k_row = ((i + 4) - 5 + (k / 3));
        sum += filter[k] * orig[k_row * 256 + k_col];
      }
      sol[i * 256 + j] = sum;
    }
  }
}