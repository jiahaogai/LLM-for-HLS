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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 1;j++) {...} */
  for (j = 1 + 1; j < 32 + 1 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      sum = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk_row:
      for (k_row = 0; k_row < 9; k_row++) {
        k = k_row - 4 + k_col;
        if ((k_row < 4) || (k_row > 4 + 27) || (k_col < 4) || (k_col > 4 + 27)) {
          sum += filter[k_row] * orig[k * 32 + j];
        }
      }
      sol[j * 32 + k_col - 4] = sum;
    }
  }
}