#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (row = 0; row < 32; row++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    inner:
    for (col = 0; col < 32; col++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      mid:
      for (k = -4; k <= 4; k++) {
        i = row + k;
        if (i < 0 || i > 31) {
          i = 1;
        }
        j = col + k;
        if (j < 0 || j > 31) {
          j = 1;
        }
        t += orig[i * 32 + j] * filter[k + 4];
      }
      sol[row * 32 + col] = t;
    }
  }
}