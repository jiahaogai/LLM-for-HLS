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
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 8192; i++) {
    sum = 0.0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    inner:
    for (j = 0; j < 9; j++) {
      k_col = i - 4 + j;
      if (k_col < 0 || k_col > 8191) {
        k_col = 0;
      }
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner_1:
      for (k = 0; k < 9; k++) {
        k_row = k - 4;
        if (k_row < 0 || k_row > 8191) {
          k_row = 0;
        }
        sum += filter[k] * orig[k_row * 8192 + k_col];
      }
    }
    sol[i] = sum;
  }
}