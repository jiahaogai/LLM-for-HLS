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
      k_row = j - 4 + k_col;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{8}
      loopk:
      for (k = 0; k < 5; k++) {
        if (((k_row + k) < 0) || ((k_row + k) > 8191)) {
          continue;
        }
        sum += filter[k_col * 5 + k] * orig[k_row + k];
      }
      sol[j] = sum;
    }
  }
}