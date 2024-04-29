#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopk_col:
    /* Standardize from: for(k_col ... ) */
    for (k_col = 0; k_col < 9; k_col++) {
      k = j + (-4 + k_col);
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      loopk_row:
      /* Standardize from: for(k_row ... ) */
      for (k_row = 0; k_row < 9; k_row++) {
        int _k = k + (-4 + k_row);
        sum += filter[k_row] * orig[(_k < 0 ? 0 : (_k > 8191 ? 8191 : _k))];
      }
      sol[j] = sum;
    }
  }
}