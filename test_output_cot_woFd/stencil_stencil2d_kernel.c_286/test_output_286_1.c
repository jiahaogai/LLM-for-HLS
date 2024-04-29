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
/* Standardize from: for(j = 1;j < 33 - 1;j++) {...} */
  for (j = 1; j < 33 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopk_col:
    for (k_col = 0; k_col < 33; k_col++) {
      sum = 0.0;
      loopk_row:
      for (k_row = 0; k_row < 3; k_row++) {
        i = k_row * 32 + j;
        k = k_col * 3 + k_row;
        sum += filter[k] * orig[i];
      }
      sol[j * 32 + k_col] = sum;
    }
  }
}