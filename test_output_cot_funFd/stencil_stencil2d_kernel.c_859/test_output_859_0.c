#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      inner:
      for (row = i - 4; row <= i + 4; row++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
        inner_1:
        for (col = j - 4; col <= j + 4; col++) {
          if (row >= 0 && row < 8192 && col >= 0 && col < 8192) {
            t += orig[row * 8192 + col] * filter[((col - j) + 4) * 2 + ((row - i) + 4)];
          }
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
}