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
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8; j++) {
      sum = 0.0;
      inner:
      for (k_col = -4; k_col < 5; k_col++) {
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
        for (k_row = -4; k_row < 5; k_row++) {
          k = k_row * 8 + k_col;
          sum += filter[k] * orig[i * 8 + k_col + 4] * orig[j * 8 + k_row + 4];
        }
      }
      sol[i * 8 + j] = sum;
    }
  }
}