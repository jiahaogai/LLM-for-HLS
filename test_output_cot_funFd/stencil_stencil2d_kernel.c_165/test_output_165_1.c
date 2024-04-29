#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 64; j++) {
      sol[i * 64 + j] = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = k % 3;
        k_row = k / 3;
        mult = filter[k] * orig[i * 64 + (j + k_col - 1) % 64 + (k_row - 1) * 64];
        sol[i * 64 + j] += mult;
      }
    }
  }
}