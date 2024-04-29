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
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopk_col:
    /* Standardize from: for(k_col ... ) */
    for (k_col = 0; k_col < 32; k_col++) {
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{32}
      loopk_row:
      /* Standardize from: for(k_row ... ) */
      for (k_row = 0; k_row < 32; k_row++) {
        int k = k_row * 32 + k_col;
        double filter_elem = filter[k_row * 32 + k_col];
        double orig_elem = orig[k];
        sum += filter_elem * orig_elem;
      }
      sol[j * 32 + k_col] = sum;
    }
  }
}