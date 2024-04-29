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
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 33 - 1; i++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk_col:
      for (k_col = -1; k_col < 2; k_col++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loopk_row:
        for (k_row = -1; k_row < 2; k_row++) {
          k = k_row * 32 + k_col + 1;
          sum += filter[k] * orig[i + k_col + ((j + k_row - 1) * 32)];
        }
      }
      sol[i + ((j - 1) * 32)] = sum;
    }
  }
}