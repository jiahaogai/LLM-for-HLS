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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  while (row < 32) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    while (col < 32) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      for (k = -4; k < 5; k++) {
        i = row + k;
        if (i < 0 || i > 31) {
          i = 0;
        }
        
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
        for (j = -4; j < 5; j++) {
          if (i == 0 && j == 0) {
            continue;
          }
          else {
            col = (32 + j);
            if (col > 79) {
              col = 79;
            }
            t += orig[i * 80 + col] * filter[k + 4];
          }
        }
      }
      sol[row * 32 + col] = t;
      col++;
    }
    row++;
  }
}