#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int col;
  int temp_row;
  int temp_col;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopj:
/* Standardize from: for(j = 1;j < 8;j++) {...} */
  for (j = 1; j < 8; j++) {
    temp_row = 8 * j;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 8; k_col++) {
      col = k_col + temp_row;
      result = 0;
      
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        row = k + col - 8;
        result += filter[k] * orig[row];
      }
      sol[col] = result;
    }
  }
}