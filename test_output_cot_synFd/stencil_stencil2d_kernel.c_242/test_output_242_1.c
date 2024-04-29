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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      sum = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k_col = -4; k_col < 5; k_col++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (k_row = -4; k_row < 5; k_row++) {
          k = k_row * 8192 + k_col;
          sum += filter[k + 4] * orig[k];
        }
      }
      sol[i * 8192 + j] = sum;
    }
  }
}