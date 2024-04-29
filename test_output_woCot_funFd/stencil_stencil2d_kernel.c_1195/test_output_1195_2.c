#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  int flen;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  flen = 9;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{62}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  row = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  while (row < 64) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    col = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    while (col < 64) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      for (i = -4; i < 5; i++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{2}
        for (j = -4; j < 5; j++) {
          int x;
          x = row + i;
          int y;
          y = col + j;
          if (x < 0 || x > 63 || y < 0 || y > 63) {
            t += filter[flen + i];
          }
          
#pragma ACCEL OFFSET auto{1}
          else {
            t += orig[x * 64 + y] * filter[flen + i];
          }
        }
      }
      sol[row * 64 + col] = t;
      col++;
    }
    row++;
  }
}