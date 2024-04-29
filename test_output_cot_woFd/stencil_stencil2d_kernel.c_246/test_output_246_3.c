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
  for (j = 8; j < 9000 - 8; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      sum = 0.0;
      loopk_row:
      for (k_row = 0; k_row < 9; k_row++) {
        k = k_row + (8 - j);
        if (k < 0) {
          k += 8;
        }
        else {
          if (k > 7) {
            k -= 8;
          }
        }
        sum += filter[k_row] * orig[k * 8 + k_col];
      }
      sol[j * 8 + k_col] = sum;
    }
  }
}