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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  flen = 9;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  row = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loop_row:
  while (row < 81) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_col:
    while (col < 81) {
      sol[row * 81 + col] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_k:
      for (k = 0; k < 9; k++) {
        i = row - 4 + k / 3;
        j = col - 4 + k % 3;
        sol[row * 81 + col] += orig[i * 81 + j] * filter[k];
      }
      col++;
    }
    row++;
  }
}