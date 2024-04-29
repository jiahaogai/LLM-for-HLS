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
  int sol_row_up;
  int sol_row_down;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 0;j < 32;j++) {...} */
  for (j = 0; j <= 31; j++) {
    int _in_j = 0 + 32L * j;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 0;k < 32;k++) {...} */
    for (k = 0; k <= 31; k++) {
      int _in_k = _in_j + 32L * k;
      k_col = 32L * k;
      row = 32L * j;
      row_up = row - 32L;
      row_down = row + 32L;
      r = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopr:
      for ( ; r < 32; r++) {
        int _in_r = _in_k + r;
        orig_row_up = row_up + r;
        orig_row_down = row_down + r;
        sol_row_up = row_up + (r - 1);
        sol_row_down = row_down + (r - 1);
        int sum = ((orig[orig_row_up] + orig[orig_row_down]) + (sol[sol_row_up] + sol[sol_row_down])) - (orig[ _in_r ] + sol[ _in_r ]);
        sol[ _in_r ] = filter[0] * sum;
      }
    }
  }
}