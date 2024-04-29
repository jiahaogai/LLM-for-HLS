#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row_up;
  int row_down;
  int row;
  int col;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 8192 - 1;j++) {...} */
  for (j = 1; j < 8192 - 1; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      sum = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = 0; k < 8; k++) {
        row_up = j - 1 - k;
        row_down = j + k;
        row = (row_up < 0) ? 0 : ((row_down >= 8192) ? 8191 : row_down);
        sum += filter[k_col * 8 + k] * orig[row * 8192 + i];
      }
      sol[j * 8192 + i] = sum;
    }
  }
}