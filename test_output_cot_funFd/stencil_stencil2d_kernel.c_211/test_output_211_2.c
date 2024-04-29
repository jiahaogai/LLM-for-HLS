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
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  flen = 9;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{62}
  row = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{62}
  while (row < 64) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    col = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    while (col < 64) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (i = -4; i < 5; i++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (j = -4; j < 5; j++) {
          t += filter[((i + 4) * 9) + (j + 4)] * orig[((row + i)) * 64 + (col + j)];
        }
      }
      sol[row * 64 + col] = t;
      col++;
    }
    row++;
  }
}