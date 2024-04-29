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
  outer:
  for (i = 0; i < 8192; i++) {
    sum = 0.0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    inner:
    for (j = 0; j < 9; j++) {
      k_col = i % 64;
      k_row = (i - k_col) / 64;
      k = ((k_row + 4) % 8) * 8 + (k_col + 4) % 8;
      sum += filter[j] * orig[k];
    }
    sol[i] = sum;
  }
}