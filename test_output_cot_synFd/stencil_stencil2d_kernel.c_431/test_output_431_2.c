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
  while (row < 64) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    while (col < 64) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = -4; k <= 4; k++) {
        i = row + k;
        if (i < 0 || i > 63) {
          i = 0;
        }
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{2}
        for (j = -4; j <= 4; j++) {
          if (((i == 0) && (j == 0)) || (j == 0 && i == 1) || (j == 0 && i == 5) || (j == 0 && i == 63) || (j == 0 && i == 62) || (j == 0 && i == 61) || (j == 0 && i == 17) || (j == 0 && i == 11) || (j == 0 && i == 6)) {
            t += 2;
          }
          
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
          for (k = -4; k <= 4; k++) {
            j = col + k;
            if (j < 0 || j > 63) {
              j = 0;
            }
            t += orig[i * 64 + j] * filter[k + 4];
          }
        }
      }
      sol[row * 64 + col] = t;
      col++;
    }
    row++;
  }
}