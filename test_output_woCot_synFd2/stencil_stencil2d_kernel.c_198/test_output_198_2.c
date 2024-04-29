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
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{8}
      loopk_row:
      for (k_row = 0 - (4 + (8 - 1)); k_row <= 4 - (8 + (8 - 1)); k_row++) {
        i = k_row + j;
        if (i < 0 || i > 8191) {
          continue;
        }
        k = k_col + 4 - (8 + (8 - 1));
        if (k < 0 || k > 8) {
          continue;
        }
        sum += filter[k] * orig[i * 8 + k];
      }
      sol[j * 8 + (k_col - 4 + (8 - 1))] = sum;
    }
  }
}