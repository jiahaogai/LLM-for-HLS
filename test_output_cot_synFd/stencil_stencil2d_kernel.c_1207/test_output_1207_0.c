#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loopj:
  for (j = 8; j < 8184; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
    for (k_col = 1; k_col < 9; k_col++) {
      k = j - 8 + k_col;
      sum = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      loopk_row:
      for (k_row = 0; k_row < 9; k_row++) {
        if (0 <= k + k_row && k + k_row < 8192) {
          sum += filter[k_row] * orig[k + k_row];
        }
      }
      sol[j] = sum;
    }
  }
}