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
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  loopj:
  for (j = 8; j < 8184; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    loopk_col:
    for (k_col = 1; k_col < 9; k_col++) {
      sum = 0.0;
      loopk_row:
      for (k_row = 0; k_row < 9; k_row++) {
        k = k_row * 9 + k_col;
        sum += filter[k] * orig[j - 4 + k_row];
      }
      sol[j - 8 + k_col] = sum;
    }
  }
}