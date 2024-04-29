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
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 256; j++) {
      sum = 0.0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k_col = -4; k_col < 5; k_col++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{7}
        for (k_row = -4; k_row < 5; k_row++) {
          k = k_row * 256 + k_col;
          sum += filter[k + 4] * orig[i * 256 + j + k_col];
        }
      }
      sol[i * 256 + j] = sum;
    }
  }
}