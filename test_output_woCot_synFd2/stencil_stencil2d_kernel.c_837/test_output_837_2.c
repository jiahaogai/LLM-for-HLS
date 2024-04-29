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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  flen = 9;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  row = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  while (row < 8192 - 9 + 1) {
    col = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    while (col < 8192 - 9 + 1) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{16}
      for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
          t += orig[((row + i - 4) % (8192 - 9 + 1)) * 8192 + ((col + j - 4) % (8192 - 9 + 1)) ] * filter[i * 9 + j];
        }
      }
      sol[row * 8192 + col] = t;
      col++;
    }
    row++;
  }
}