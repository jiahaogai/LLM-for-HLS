#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 8; j < 8184; j += 8) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k_col = -4; k_col <= 4; k_col += 1) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (k_row = -4; k_row <= 4; k_row += 1) {
          k = (8192 + (k_row * 8) + k_col);
          sum += filter[(((4 + k_row) * 9) + (4 + k_col)) - 25] * orig[k];
        }
      }
      sol[i * 8192 + j] = sum;
    }
  }
}