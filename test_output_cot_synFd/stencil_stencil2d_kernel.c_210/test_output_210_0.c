#pragma ACCEL kernel

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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  while (row < 32) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    while (col < 32) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
      for (k = -4; k <= 4; k++) {
        i = row + k;
        if (i < 0 || i > 31) {
          i = 0;
        }
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        for (j = -4; j <= 4; j++) {
          if (((col + j) < 0) || ((col + j) > 31)) {
            t += orig[i * 32] * filter[j + 4];
          }
           else {
            t += orig[i * 32 + (col + j)] * filter[j + 4];
          }
        }
      }
      sol[row * 32 + col] = t;
      col++;
    }
    row++;
  }
}