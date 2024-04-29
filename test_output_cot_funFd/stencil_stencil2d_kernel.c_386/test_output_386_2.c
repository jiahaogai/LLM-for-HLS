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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  loopj:
  for (j = 2; j < 128 - 2; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    loopk:
    for (k = 2; k < 64 - 2; k++) {
      t = 0;
      loopx:
      for (row = -2; row <= 2; row++) {
        loopy:
        for (col = -2; col <= 2; col++) {
          i = j + row;
          if (i < 0) {
            i = 0;
          }
           else if (i > 127) {
            i = 127;
          }
          t += orig[i * 64 + k + col] * filter[row * 3 + col + 2];
        }
      }
      sol[j * 64 + k] = t;
    }
  }
}