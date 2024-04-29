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
  int col;
  int col_up;
  int col_down;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 0; j < 32; j++) {...} */
  for (j = 0; j <= 31; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 0; k_col < 32; k_col++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      loopk:
      for (k = 0; k < 9; k++) {
        i = k + (32 * j);
        sum += filter[k] * orig[i + k_col];
      }
      sol[j * 32 + k_col] = sum;
    }
  }
}