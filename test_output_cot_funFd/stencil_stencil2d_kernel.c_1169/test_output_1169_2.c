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
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  outer:
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 1; j < 8191; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        row = i - 4 + k;
        col = j - 4;
        if (row < 0 || 8191 < row || col < 0 || 8191 < col) {
          sum += 0.0;
        }
         else {
          sum += filter[k] * orig[row * 8192 + col];
        }
      }
      sol[i * 8192 + j] = sum;
    }
  }
}