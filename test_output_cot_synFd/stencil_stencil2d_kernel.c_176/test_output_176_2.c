Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int col;
  row = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  while (row < 32) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    while (col < 32) {
      t = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      while (t < 9) {
        k = t - 4;
        j = row + k;
        if (j < 0 || j > 31) {
          j = 0;
        }
        k = col + k;
        if (k < 0 || k > 31) {
          k = 0;
        }
        i = j * 32 + k;
        t = t + 1;
        sol[row * 32 + col] = orig[i] * filter[t];
      }
      col = col + 1;
    }
    row = row + 1;
  }
}