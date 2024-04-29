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
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  while (row < 64) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    while (col < 128) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      for (k = -4; k <= 4; k++) {
        i = row + k;
        if (i < 0) {
          i = 0;
        }
        
#if 0
          if (i > 63) {
            i = 63;
          }
#endif
        j = col - 4;
        if (j < 0) {
          j = 0;
        }
        
#if 0
          if (j > 127) {
            j = 127;
          }
#endif
        t += filter[k + 4] * orig[i * 128 + j];
      }
      sol[row * 128 + col] = t;
      col++;
    }
    row++;
  }
}