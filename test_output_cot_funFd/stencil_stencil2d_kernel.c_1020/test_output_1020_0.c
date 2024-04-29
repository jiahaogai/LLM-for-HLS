#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  loop_row:
  for (row = 1; row < 8191; row++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_col:
    for (col = 1; col < 8191; col++) {
      sum = 0.0;
      loop_k:
      for (k = 0; k < 9; k++) {
        i = row - 4 + k / 3;
        j = col - 4 + k % 3;
        sum += filter[k] * orig[i * 8192 + j];
      }
      sol[row * 8192 + col] = sum;
    }
  }
}