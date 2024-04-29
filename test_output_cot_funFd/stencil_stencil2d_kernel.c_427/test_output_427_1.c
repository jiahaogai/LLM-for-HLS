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
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 16; i < 8172 - 16; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 16; j < 8192 - 16; j++) {
      sum = 0.0;
      k_col = j - 16 + 16;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        k_row = i - 16 + ((8 - 1) + k);
        sum += filter[k] * orig[k_row * 8192 + k_col];
      }
      sol[i * 8192 + j] = sum;
    }
  }
}