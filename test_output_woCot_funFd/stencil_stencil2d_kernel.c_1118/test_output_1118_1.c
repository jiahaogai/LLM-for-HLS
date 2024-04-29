#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[2][2])
{
  int i;
  int j;
  int fl;
  int fs;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 1; i < 3; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 3; j++) {
      fl = filter[0][0] * orig[i - 1][j - 1];
      fs = filter[0][1] * orig[i - 1][j];
      sol[i][j] = fl + fs;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 3; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 3; j++) {
      fl = filter[1][0] * sol[i - 1][j - 1];
      fs = filter[1][1] * sol[i - 1][j];
      sol[i][j] = fl + fs;
    }
  }
}