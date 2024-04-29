#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int col;
  col = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  while (col < 256) {
    row = 0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    while (row < 256) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      kernel:
      for (k = -4; k <= 4; k++) {
        i = row + k;
        if (i < 0 || i > 255) {
          i = 0;
        }
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        for (j = -4; j <= 4; j++) {
          int cur;
          int flt;
          i = row + k;
          j = col + j;
          if (i < 0 || i > 255) {
            i = 0;
          }
          
          if (j < 0 || j > 255) {
            j = 0;
          }
          
          cur = orig[i * 256 + j];
          flt = filter[k + 4];
          t += cur * flt;
        }
      }
      sol[row * 256 + col] = t;
      row++;
    }
    col++;
  }
}