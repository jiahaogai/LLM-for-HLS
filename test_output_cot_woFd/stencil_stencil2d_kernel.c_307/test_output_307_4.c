#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 8191;j++) {...} */
  for (j = 1; j < 8191; j++) {
    i_col = 8;
    loopk_col:
/* Standardize from: for(k_col = 0;k_col < 8;k_col++) {...} */
    for (k_col = 0; k_col < 8; k_col++) {
      i = j - 4 + k_col;
      sum = ((double )0);
      loopk:
/* Standardize from: for(k = -4;k < 5;k++) {...} */
      for (k = -4; k < 5; k++) {
        sum += filter[k + 4] * orig[i + k];
      }
      sol[j] = sum;
      i_col--;
    }
  }
}