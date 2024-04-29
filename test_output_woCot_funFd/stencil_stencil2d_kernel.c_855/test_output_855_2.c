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
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8192 >> 1) + i - 4 + ((9 - 1) >> 1) - k);
        k_col = (k_col > -1 ? (k_col < 8192 ? k_col : -1) : -1);
        k_row = ((8192 >> 1) + j - 4 + ((9 - 1) >> 1) - k);
        k_row = (k_row > -1 ? (k_row < 8192 ? k_row : -1) : -1);
        if (k_col == -1 || k_row == -1) {
          sum += filter[k] * 0.0;
        }
         else {
          sum += filter[k] * orig[k_row * 8192 + k_col];
        }
      }
      sol[i * 8192 + j] = sum;
    }
  }
}