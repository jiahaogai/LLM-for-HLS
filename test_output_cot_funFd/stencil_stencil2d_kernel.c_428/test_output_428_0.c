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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{18}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{11}
    for (j = 1; j < 8191; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k_col = -4; k_col <= 4; k_col++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        for (k_row = -4; k_row <= 4; k_row++) {
          k = k_row + 4 + ((k_col + 4) * 32);
          sum += filter[k] * orig[i + k_row + 1 + ((j + k_col + 1) * 32)];
        }
      }
      sol[i + ((j + 1) * 32)] = sum;
    }
  }
}