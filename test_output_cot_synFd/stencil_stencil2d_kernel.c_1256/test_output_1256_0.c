#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int row;
  int col;
  int temp;
  int mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
/* Standardize from: for(k_col ... ) */
    for (k_col = 0; k_col < 9; k_col++) {
      k_row = k_col;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopk_row:
/* Standardize from: for(k_row ... ) */
      for (k_row = 0; k_row < 9 - 1; k_row++) {
        k = k_row * 9 + k_col;
        row = j - 1 + k_row;
        col = k_col - 5;
        temp = orig[row * 32 + col];
        mul = temp * filter[k];
        sol[j * 32 + k_col - 5] = mul;
      }
    }
  }
}