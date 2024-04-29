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
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8192 == 1) ? 8191 : 8192) * (k % 8192);
        k_row = (8192 == 1) ? 8191 : 8192;
        sum += filter[k] * orig[i + k_row - 4 + ((j + k_col - 4) < 0 ? 0 : ((j + k_col - 4) > 8191 ? 8191 : (j + k_col - 4)))];
      }
      sol[i * (8192 == 1 ? 1 : 8192) + j] = sum;
    }
  }
}