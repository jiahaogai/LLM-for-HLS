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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = i - 4 + k % 5;
        if (k_col < 0 || k_col > 8191) {
          k_col = 0;
        }
        k_row = j - 4 + k / 5;
        if (k_row < 0 || k_row > 8) {
          k_row = 0;
        }
        sum += filter[k] * orig[k_row * 8192 + k_col];
      }
      sol[j * 8192 + i] = sum;
    }
  }
}