#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 64; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        row = i + ((k / 3) - 1);
        col = j + ((k % 3) - 1);
        if (((row < 0) || (row > 127)) || ((col < 0) || (col > 63))) {
          sum += 0.0;
        }
         else {
          sum += orig[row * 64 + col] * filter[k];
        }
      }
      sol[i * 64 + j] = sum;
    }
  }
}