#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[256])
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
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  while (row < 256) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    while (col < 256) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      for (k = -128; k <= 128; k++) {
        i = row + k;
        if (i < 0 || i > 255) {
          i = 0;
        }
        j = col + k;
        if (j < 0 || j > 255) {
          j = 0;
        }
        t += ((int )filter[k + 128]) * orig[i * 256 + j];
      }
      sol[row * 256 + col] = t;
      col += 1;
    }
    row += 1;
  }
}