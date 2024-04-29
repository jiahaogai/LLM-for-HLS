#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 8192; i++) {
    inner:
    for (j = 0; j < 8192; j++) {
      int sum = 0;
      int k_row = -1 * pad;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      row:
      while (k_row < pad) {
        int k_col = -1 * pad;
        
#pragma ACCEL PIPELINE auto{flatten}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        col:
        while (k_col < pad) {
          k++;
          k_col++;
          sum += filter[k] * orig[i + k_row * 8192 + k_col];
        }
        k_row++;
      }
      sol[i * 8192 + j] = sum;
    }
  }
}