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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  flen = 9;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 0; j < 32; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 0; i < 32; i++) {
      t = 0;
      loopfilter:
      for (row = -4; row <= 4; row++) {
        loopcol:
        for (col = -4; col <= 4; col++) {
          int x;
          x = i + col;
          int y;
          y = j + row;
          /*
          * In order to avoid border problems the following
          * two rules are used
          * 1. if the value to be read is before the start of the matrix
          *    then we get the value from the start
          * 2. if the value to be read is after the end of the matrix
          *    then we get the value from the end
          */
          if (x < 0) {
            x = 0;
          }
          if (y < 0) {
            y = 0;
          }
          if (x >= 32) {
            x = 31;
          }
          if (y >= 32) {
            y = 31;
          }
          t += filter[row * 9 + col] * orig[y * 32 + x];
        }
      }
      sol[j * 32 + i] = t;
    }
  }
}