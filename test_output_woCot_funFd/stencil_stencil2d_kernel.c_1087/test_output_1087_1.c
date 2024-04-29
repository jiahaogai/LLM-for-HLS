#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[25][25])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{6}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = ((orig[i - 1][j - 1] + orig[i - 1][j] + orig[i - 1][1 + j] + orig[i][j - 1] + orig[i][j] + orig[i][1 + j] + orig[1 + i][j - 1] + orig[1 + i][j] + orig[1 + i][1 + j]) / 9) + filter[i][j];
    }
  }
}