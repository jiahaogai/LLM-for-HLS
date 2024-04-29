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
/* Standardize from: for(j = 0;j < 64;j++) {...} */
  for (j = 0; j < 64; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      col = j - 4 + k_col;
      if (((col >= 0) && (col < 64))) {
        temp = 0;
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loopk_row:
        for (k_row = 0; k_row < 9; k_row++) {
          row = k_row - 4 + i;
          if (((row >= 0) && (row < 64))) {
            k = row * 64 + col;
            temp += orig[k] * filter[k_row * 9 + k_col];
          }
        }
        sol[i * 64 + j] = temp;
      }
    }
  }
}