Code: 
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
      loopk:
/* Standardize from: for(k ... ) */
      for (k = 0; k < 9; k++) {
        if (k_row < 9) {
          k_row++;
          continue;
        }
        row = j - 2 + (k_col - 4);
        col = i - 2 + (k_row - 4);
        temp = 0;
        loopsum:
/* Standardize from: for(sum ...  ) */
        for (sum = 0; sum < 9; sum++) {
          temp += filter[k * 9 + sum] * orig[row * 64 + col + sum - 4];
        }
	sol[j * 64 + i] = temp;
      }
    }
  }
}