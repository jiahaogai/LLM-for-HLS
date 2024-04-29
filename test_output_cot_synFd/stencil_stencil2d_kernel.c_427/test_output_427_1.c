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
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 8; j++) {
      sum = 0.0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = 0; k < 81; k++) {
        k_col = i - 4 + k % 8;
        k_row = j + k / 8;
        if (k_col < 0 || k_col > 8191) {
          k_col = 0;
        }
        if (k_row < 0 || k_row > 8) {
          k_row = 0;
        }
        sum += filter[k] * orig[k_row * 81 + k_col];
      }
      sol[i] = sum;
    }
  }
}