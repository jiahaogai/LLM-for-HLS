#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int elem;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 32; j++) {
      elem = 0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8 * i) + (k % 3));
        k_row = ((8 * j) + (k / 3));
        elem += filter[k] * orig[k_row * 32 + k_col];
      }
      sol[i * 32 + j] = elem;
    }
  }
}