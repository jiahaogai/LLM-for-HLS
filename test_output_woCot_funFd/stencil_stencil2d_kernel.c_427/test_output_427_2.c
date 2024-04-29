#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{stencil_label1}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{stencil_label2}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    /* Standardize from: for(k_col ... ) */
    for (k_col = 0; k_col < 8; k_col++) {
      sum = 0.0;
      loopk_row:
      /* Standardize from: for(k_row ... ) */
      for (k_row = 0 - 4 + 1; k_row <= 4 - 1; k_row++) {
        i = k_row + j;
        if ((((i >= 1) && (i <= 8192))) && (((k_col >= 1) && (k_col <= 8)))) {
          sum += filter[((k_row + 4) * 8) + k_col] * orig[i];
        }
      }
      sol[j] = sum;
    }
  }
}