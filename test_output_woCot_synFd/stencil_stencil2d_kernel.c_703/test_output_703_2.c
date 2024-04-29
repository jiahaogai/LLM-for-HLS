#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int row_up;
  int row_down;
  int r;
  int orig_row_up;
  int orig_row_down;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 0;j < 32;j++) {...} */
  for (j = 0; j <= 31; j++) {
    int tmp_j;
    tmp_j = 0 + 32 * j;
    int orig_j;
    orig_j = tmp_j;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 0;k < 32;k++) {...} */
    for (k = 0; k <= 31; k++) {
      int tmp_k;
      tmp_k = 0 + 32 * k;
      int sum;
      sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{8}
      loopk_col:
      for (k_col = 0; k_col <= 8; k_col++) {
        int tmp_k_col;
        tmp_k_col = (0 + 32 * k) + k_col;
        int orig_index;
        orig_index = tmp_k_col;
        sum += orig[orig_index] * filter[k_col];
      }
      int sol_index;
      sol_index = tmp_j + tmp_k;
      sol[sol_index] = sum;
    }
  }
}