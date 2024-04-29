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
  
#pragma ACCEL TILE FACTOR=auto{126}
  loopj:
/* Standardize from: for(j ... */
  for (j = 1; j < 33 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
/* Standardize from: for(k_col ... */
    for (k_col = 1; k_col < 33 - 1; k_col++) {
      temp_row = j - 1;
      row = ((4096 * temp_row) + 64);
      temp_col = k_col - 1;
      col = ((64 * temp_col) + 1);
      result = 0;
      
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{1}
      loopk:
/* Standardize from: for(k ... */
      for (k = 0; k < 9; k++) {
        result += ((filter[k]) * (orig[row + align(k, (64 * 8)) + col] ));
      }
      sol[row + col] = result;
    }
  }
}