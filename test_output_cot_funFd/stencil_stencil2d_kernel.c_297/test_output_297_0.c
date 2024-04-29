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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 2; j < 64 - 2; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopk_col:
/* Standardize from: for(k_col ... ) */
    for (k_col = 0; k_col < 9; k_col++) {
      k_row = k_col;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk_row:
/* Standardize from: for(k_row ... ) */
      for (k_row = 0; k_row < 9; k_row++) {
        k = k_row * 9 + k_col;
        row = j + (-1 + k_row);
        col = i + (-1 + k_col);
        if (row < 0 || 64 <= row || col < 0 || 128 <= col) {
          temp = 0;
        }
         else {
          temp = orig[row * 128 + col];
        }
        temp *= filter[k];
      }
    }
    sol[j * 128 + i] = temp;
  }
}