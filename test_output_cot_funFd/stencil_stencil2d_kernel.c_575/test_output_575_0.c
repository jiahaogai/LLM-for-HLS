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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
/* Standardize from: for(k_col ... ) */
    for (k_col = 0; k_col < 9; k_col++) {
      int tmp;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{8}
      loopk_row:
/* Standardize from: for(k_row ... ) */
      for (k_row = 0; k_row < 9; k_row++) {
        int i_row;
        int i_col;
        i_row = j + (-4 + ((int )k_row));
        i_col = i + (-4 + ((int )k_col));
        if (i_row < 0 || 32 < i_row || i_col < 0 || 32 < i_col) {
          tmp = 0;
        }
         else {
          tmp = orig[i_row * 32 + i_col];
        }
        sum += filter[k_row * 9 + k_col] * tmp;
      }
      sol[j * 32 + k_col] = sum;
      sum = 0;
    }
  }
}