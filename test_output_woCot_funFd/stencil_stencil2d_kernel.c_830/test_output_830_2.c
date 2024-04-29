Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int col;
  row = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  while (row < 64) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    while (col < 64) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      for (k = -4; k <= 4; k++) {
        i = row + k;
        if (i < 0 || i >= 64) {
          i = 0;
        }
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
        for (j = -4; j <= 4; j++) {
          if (((i == 0) && (j == 0)) || ((j == -4) || (j == 4)) || ((i == 64 - 1) && (j == -4)) || ((i == 64 - 1) && (j == 4))) {
            t += filter[k + 4] * orig[i * 64 + j + 4];
          }
        }
      }
      sol[row * 64 + col] = t;
      col++;
    }
    row++;
  }
}