- '#pragma ACCEL PARALLEL FACTOR=auto{16}': Break up this loop into 16 partitions, each of which will be executed in parallel.
- '#pragma ACCEL PARALLEL FACTOR=auto{8}': Break up this loop into 8 partitions, each of which will be executed in parallel.
- '#pragma ACCEL PARALLEL FACTOR=auto{1}': Break up this loop into 1 partitions, each of which will be executed in parallel.

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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    loopk_col:
    for (k_col = 0; k_col < 8; k_col++) {
      i_col = 8 * j + k_col;
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{8}
      loopk:
      for (k = 0; k < 8; k++) {
        i = 8 * (j - 1) + k;
        sum += filter[k] * orig[i_col - 1 + k - 8];
      }
      sol[i_col] = sum;
    }
  }
}