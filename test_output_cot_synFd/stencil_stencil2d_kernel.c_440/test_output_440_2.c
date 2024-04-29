#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 64 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    loopk_col:
    /* Standardize from: for(k_col ... ) */
    for (k_col = 1; k_col < 64 - 1; k_col++) {
      sum = 0.0;
      loopk_row:
      /* Standardize from: for(k_row ... ) */
      for (k_row = 0; k_row <= 8; k_row++) {
        i = k_row * 64 + j;
        sum += filter[k_row] * orig[i * 64 + k_col];
      }
      sol[j * 64 + k_col] = sum;
    }
  }
}