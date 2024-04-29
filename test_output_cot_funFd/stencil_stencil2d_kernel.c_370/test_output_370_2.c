#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flen;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  flen = 9;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  row = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  while (row < 32) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    col = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    while (col < 32) {
      sol[row * 32 + col] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        i = row - 4 + (k / 32);
        j = col - 4 + (k % 32);
        sol[row * 32 + col] += filter[k] * orig[i * 32 + j];
      }
      col++;
    }
    row++;
  }
}