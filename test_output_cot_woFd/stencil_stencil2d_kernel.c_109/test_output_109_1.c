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
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    loopk_col:
    for (k_col = 0; k_col < 8; k_col++) {
      k = 8 * j + k_col;
      sum = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{32}
      loopk_row:
      for (k_row = 0; k_row < 8; k_row++) {
        sum += filter[k_row] * orig[k_row * 8 + k_col];
      }
      sol[k] = sum;
    }
  }
}