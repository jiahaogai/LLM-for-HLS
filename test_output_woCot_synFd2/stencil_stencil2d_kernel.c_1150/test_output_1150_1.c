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
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      inner_3:
      for (k_col = -4; k_col < 5; k_col++) {
        int k_col_idx = clipt(8191, 0, i + k_col);
        inner_2:
        for (k_row = -4; k_row < 5; k_row++) {
          int k_idx = clipt(8191, 0, k_col_idx + k_row);
          sum += filter[k_row + 4] * orig[k_idx];
        }
      }
      sol[i * 8192 + j] = sum;
    }
  }
}