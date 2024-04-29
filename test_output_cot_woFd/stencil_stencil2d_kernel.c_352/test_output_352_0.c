#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[2][2])
{
  int i;
  int j;
  int fl;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 4; j++) {
      fl = filter[0][0] * orig[i - 1][j - 1] + filter[0][1] * orig[i - 1][j] + filter[0][2] * orig[i - 1][j + 1] + filter[1][0] * orig[i][j - 1] + filter[1][1] * orig[i][j] + filter[1][2] * orig[i][j + 1];
      sol[i][j] = fl;
    }
  }
}