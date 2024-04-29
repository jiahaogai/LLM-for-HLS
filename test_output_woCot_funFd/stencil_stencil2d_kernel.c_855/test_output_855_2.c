#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k_col = -4; k_col < 5; k_col++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        inner_1:
        for (k_row = -4; k_row < 5; k_row++) {
          k = (8192 + 4) * k_row + k_col + 4;
          if (((i + k_row) >= 0) && ((i + k_row) < 8192) && ((j + k_col) >= 0) && ((j + k_col) < 8192)) {
            sum += filter[((k_row + 4) * 9) + (k_col + 4)] * orig[(8192 * (i + k_row)) + (j + k_col)];
          }
        }
      }
      sol[i * 8192 + j] = sum;
    }
  }
}