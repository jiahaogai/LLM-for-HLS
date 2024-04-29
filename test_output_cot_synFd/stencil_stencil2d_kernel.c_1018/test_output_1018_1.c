Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 0; j < 256; j++) {
      sum = 0;
      mid:
      for (k = -4; k < 5; k++) {
        row = i + k;
        if (row < 0 || 8191 < row) {
          row = i;
        }
        col = j - 4;
        if (col < 0) {
          col = 0;
        }
        if (8191 < col) {
          col = 8191;
        }
        sum += orig[row * 256 + col] * filter[k + 4];
      }
      sol[i * 256 + j] = sum;
    }
  }
}