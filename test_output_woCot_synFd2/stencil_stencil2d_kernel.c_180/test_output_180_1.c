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
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      inner:
      for (k = -4; k < 5; k++) {
        k_col = j + k;
        if (k_col < 0) {
          k_col += 8192;
        }
        else {
          if (k_col > 8191) {
            k_col -= 8192;
          }
        }
        k_row = i + k;
        if (k_row < 0) {
          k_row += 8192;
        }
        else {
          if (k_row > 8191) {
            k_row -= 8192;
          }
        }
        sum += filter[k + 4] * orig[k_row * 8192 + k_col];
      }
      sol[i * 8192 + j] = sum;
    }
  }
}