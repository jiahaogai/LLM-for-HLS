#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row_up;
  int row_down;
  int row_middle;
  int col_left;
  int col_right;
  double mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 32 - 1;j++) {...} */
  for (j = 1 + 0; j <= 32 - 1 + 0; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopk_col:
    for (k_col = 0; k_col < 8; k_col++) {
      mult = filter[k_col];
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = 1; k < 32 - 1; k++) {
        row_up = (0 + k_col * 32) + (k - 1);
        row_middle = (0 + k_col * 32) + (k);
        row_down = (0 + k_col * 32) + (k + 1);
        col_left = (j - 1) * 32;
        col_right = (j + 1) * 32;
        sol[row_middle] = mult * (orig[row_up] + orig[row_down] + orig[col_left] + orig[col_right] - orig[row_middle]);
      }
    }
  }
}