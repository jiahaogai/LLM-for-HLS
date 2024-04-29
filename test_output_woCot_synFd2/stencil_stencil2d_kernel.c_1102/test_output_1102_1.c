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
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8; j++) {
      sum = 0.0;
      inner:
      for (k_col = -1; k_col < 2; k_col++) {
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
        inner_1:
        for (k_row = -1; k_row < 2; k_row++) {
          k = k_row * 8 + k_col + 1;
          sum += filter[k] * orig[i * 8 + j + k_col];
        }
      }
      sol[i * 8 + j] = sum;
    }
  }
}