#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  row = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  while (row < 256) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{14}
    while (col < 256) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{14}
      for (i = -4; i < 5; i++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{14}
        for (j = -4; j < 5; j++) {
          t += orig[row + i][col + j] * filter[4 + i];
        }
      }
      sol[row][col] = t;
      col++;
    }
    row++;
  }
}