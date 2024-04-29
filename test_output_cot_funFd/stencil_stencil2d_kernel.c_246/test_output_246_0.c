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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  while (row < 8) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    while (col < 8) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{16}
      for (i = -4; i < 5; i++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        for (j = -4; j < 5; j++) {
          t += orig[((((row + i)) * 8) + (col + j)) ] * filter[((4 + i) * 8) + (4 + j)];
        }
      }
      sol[((row * 8) + col)] = t;
      col++;
    }
    row++;
  }
}