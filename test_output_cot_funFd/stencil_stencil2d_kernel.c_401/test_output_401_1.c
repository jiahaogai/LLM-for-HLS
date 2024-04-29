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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 2; j < 64 + 2; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
/* Standardize from: for(k_col ... ) */
    for (k_col = 0; k_col < 3; k_col++) {
      loopk_row:
/* Standardize from: for(k_row ... ) */
      for (k_row = 0; k_row < 3; k_row++) {
        i = 1 + 64 * (1 + 3 * k_row);
        row = i - 2 + j;
        col = 1 + 3 * k_col;
        temp = filter[k_row * 3 + k_col] * orig[row * 64 + col];
        sol[row * 64 + col] = temp;
      }
    }
  }
}