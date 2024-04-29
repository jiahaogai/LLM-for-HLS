#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64; j++) {
      s = 0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8 * i) + (k % 3));
        k_row = ((8 * j) + (k / 3));
        idx = (k_row * 64) + k_col;
        s += filter[k] * orig[idx];
      }
      sol[(i * 64) + j] = s;
    }
  }
}