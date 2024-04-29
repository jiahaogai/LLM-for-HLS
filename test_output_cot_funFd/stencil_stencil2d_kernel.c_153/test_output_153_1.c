#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  row = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  while (row < 256) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    while (col < 256) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (i = -4; i < 5; i++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
        for (j = -4; j < 5; j++) {
          t += orig[((((row + i)) * 256) + (col + j)) ] * filter[((i + 4) * 9) + (j + 4)];
        }
      }
      sol[((row * 256) + col)] = t;
      col++;
    }
    row++;
  }
}