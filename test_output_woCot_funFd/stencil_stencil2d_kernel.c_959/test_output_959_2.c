#
#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[9])
{
  int fidx;
  int i;
  int j;
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
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      filter_idx:
      for (fidx = 0; fidx < 9; fidx++) {
        tmp += filter[fidx] * orig[i + ((4 - 1) >> 1) + ((fidx - 4) >> 1)][j + ((4 - 1) >> 1) + ((fidx - 4) >> 1)];
      }
      sol[i][j] = tmp;
    }
  }
}