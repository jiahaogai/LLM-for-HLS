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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      sum = 0;
      inner:
      for (k = 0; k < 9; k++) {
        row = i + ((k - 4) >> 8);
        col = j + ((k - 4) & 255);
        if (row < 0 || 256 <= row || col < 0 || 256 <= col) {
          /* Nothing */
        }
         else {
          sum += orig[row * 256 + col] * filter[k];
        }
      }
      sol[i * 256 + j] = sum;
    }
  }
}