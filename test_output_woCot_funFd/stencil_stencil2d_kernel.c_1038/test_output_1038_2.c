#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  int flen;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  flen = 9;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  row = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  while (row < 32) {
    col = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    while (col < 32) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      for (i = -4; i < 5; i++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{4}
        for (j = -4; j < 5; j++) {
          t += orig[((((row + i)) * 32) + (col + j))] * filter[((i + 4) * 9) + (j + 4)];
        }
      }
      sol[((row * 32) + col)] = t;
      col++;
    }
    row++;
  }
}