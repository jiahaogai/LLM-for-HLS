#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      row = i - 4;
      col = j - 4;
      k = 0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      while (row < i + 5) {
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        while (col < j + 5) {
          k += orig[row * 8192 + col] * filter[k];
          col += 1;
        }
        row += 1;
        col = j - 4;
      }
      sol[i * 8192 + j] = k;
    }
  }
}