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
  for (row = 0; row < 64; row++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (col = 0; col < 64; col++) {
      t = 0;
      inner_1:
      for (k = -4; k < 5; k++) {
        i = row + k;
        inner_2:
        for (j = -4; j < 5; j++) {
          if (((i >= 0) && (i < 64)) && ((j >= 0) && (j < 64))) {
            t += filter[k + 4] * orig[i * 64 + j] ;
          }
        }
      }
      sol[row * 64 + col] = t;
    }
  }
}