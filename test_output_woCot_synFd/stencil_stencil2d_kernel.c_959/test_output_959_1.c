#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[9])
{
  int i;
  int j;
  int fltr;
  int tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 0; j < 4; j++) {
      tmp = 0;
      inner_filter:
      for (fltr = 0; fltr < 9; fltr++) {
        tmp += orig[i + ((4 - 1) >> 1) + ((4 - 9) >> 1) * (fltr >> 1)][j + ((4 - 1) >> 1) + ((4 - 9) >> 1) * (fltr & 1)] * filter[fltr];
      }
      sol[i][j] = tmp;
    }
  }
}