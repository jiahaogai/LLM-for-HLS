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
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  loop_row:
  while (row < 80) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loop_col:
    while (col < 80) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{14}
      loop_k:
      for (k = 0; k < 9; k++) {
        i = row + ((k / 3) - 1);
        j = col + ((k % 3) - 1);
        if (i >= 0 && i < 80 && j >= 0 && j < 80) {
          t += orig[i * 80 + j] * filter[k];
        }
      }
      sol[row * 80 + col] = t;
      col++;
    }
    row++;
  }
}