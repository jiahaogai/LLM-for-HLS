#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
=======
  int k_col;
  int row;
  int col;
  int temp_row;
  int temp_col;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
<<<<<<< HEAD
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 9; j++) {
      int curr = filter[j];
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      inner:
      for (k = 0; k < 8; k++) {
        result = curr * orig[i * 8 + k] + sol[i * 8 + k];
        sol[i * 8 + k] = result;
      }
=======
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
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}