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
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8; j++) {
      sum = 0.0;
      inner:
      for (k_col = -1; k_col <= 1; k_col++) {
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
        for (k_row = -1; k_row <= 1; k_row++) {
          k = i * 8 + k_row;
          if (k < 0) {
            k = 0;
          }
          else if (k > 7) {
            k = 7;
          }
          k = k * 8 + j + k_col;
          sum += filter[k_row + 1] * filter[k_col + 1] * orig[k];
        }
      }
      sol[i * 8 + j] = sum;
    }
  }
}