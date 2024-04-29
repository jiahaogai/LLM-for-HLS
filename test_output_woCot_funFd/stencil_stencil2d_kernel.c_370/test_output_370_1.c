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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner:
      for (k = -4; k < 5; k++) {
        row = i + k;
        if (row < 0 || 256 <= row) {
          row = i;
        }
        col = j - 4;
        if (col < 0) {
          col = 0;
        }
        if (256 <= col) {
          col = 255;
        }
        sum += filter[k + 4] * orig[row * 256 + col];
      }
      sol[i * 256 + j] = sum;
    }
  }
}