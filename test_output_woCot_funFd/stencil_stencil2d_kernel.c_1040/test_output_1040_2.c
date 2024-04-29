#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{62}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      i_col = i - 4;
      k_col = 0;
      
      inner:
      while (k_col < 9) {
        k = k_col + 4;
        if (((i_col + k_col) >= 0) && ((i_col + k_col) < 8192)) {
          sum = ((double )0);
          idx_row:
          for (k = k_col; k < 9 + k_col; k++) {
            idx_col:
            for (j = 0; j < 8; j++) {
              sum += filter[k] * orig[i_col + k - 4 + (j + 4) * 8192];
            }
          }
          sol[i_col + k_col + (j + 0) * 8192] = sum;
        }
        k_col++;
      }
    }
  }
}