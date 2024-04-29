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
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    inner:
    for (j = 0; j < 32; j++) {
      sum = 0.0;
      inner_3:
      for (k_col = 0; k_col < 9; k_col++) {
        k_row = i - 4 + k_col;
        if ((((i < 4) || (i > 27)) || ((j < 4) || (j > 27))) || ((k_row < 0) || (k_row > 27))) {
          k = 0;
        }
         else {
          k = k_row * 32 + j - 4;
        }
        sum += filter[k_col] * orig[k];
      }
      sol[i * 32 + j] = sum;
    }
  }
}