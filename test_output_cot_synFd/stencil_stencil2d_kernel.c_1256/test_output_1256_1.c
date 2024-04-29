#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int offset;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  loopj:
/* Standardize from: for(j = 1;j < 33 - 1;j++) {...} */
  for (j = 1 + 0; j < 33 - 1 + 0; j++) {
    int _in_j = 0 + 1 * 32L + j;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 1; k_col < 33 - 1; k_col++) {
      int _in_k_col = (0 + 1 * 32L) + k_col;
      temp = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk_row:
      for (k_row = 1; k_row < 33 - 1; k_row++) {
        int _in_k_row = ((0 + 1 * 32L) + k_row) * 32L;
        int _in_k = ((0 + 1 * 32L) + k_row) * 33L + k_col;
        temp += orig[_in_k] * filter[k_row * 33L + k_col];
      }
      sol[_in_j] = temp;
    }
  }
}