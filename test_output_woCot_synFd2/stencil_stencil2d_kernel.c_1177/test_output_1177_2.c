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
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  loopj:
/* Standardize from: for(j = 1;j < 8192 - 1;j++) {...} */
  for (j = 1 + 8192 * 0; j < 1 + 8192 * 14; j += 8192 * 14) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 1; k_col < 8; k_col++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
      loopk_row:
      for (k_row = 1; k_row > -8; k_row--) {
        i = k_row + j;
        sum += filter[k_col + 4] * orig[i - 4 + (k_col + 4) * 8];
      }
      sol[j + (k_col + 4) * 8] = sum;
    }
  }
}