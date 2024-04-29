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
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      sum = 0.0;
      inner:
      for (k_col = -1; k_col < 2; k_col++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (k_row = -1; k_row < 2; k_row++) {
          k = (256 + i + k_row) % 256;
          j_tmp = (256 + j + k_col) % 256;
          sum += filter[((k_row + 1) * 3) + (k_col + 1)] * orig[k * 256 + j_tmp];
        }
      }
      sol[i * 256 + j] = sum;
    }
  }
}