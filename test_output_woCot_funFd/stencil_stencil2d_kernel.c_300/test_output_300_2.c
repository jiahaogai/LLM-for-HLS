#pragma ACCEL kernel

void stencil(double orig[400][400],double sol[400][400],double filter[4][4])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 400 - 1; j++) {
      sum = 0.0;
      inner:
      for (k_col = -1; k_col < 2; k_col++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        inner_1:
        for (k_row = -1; k_row < 2; k_row++) {
          k = k_row + 1;
          sum += filter[k_row][k_col] * orig[i + k_row][j + k_col];
        }
      }
      sol[i][j] = sum;
    }
  }
}