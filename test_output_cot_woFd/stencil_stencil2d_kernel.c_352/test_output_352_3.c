#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[2][2])
{
  int i;
  int j;
  int fl;
  int ol;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 0; j < 4; j++) {
      fl = filter[0][0] * orig[i][j] + filter[0][1] * orig[i][j + 1] + filter[1][0] * orig[i][j + 2] + filter[1][1] * orig[i][j + 3];
      ol = i * 4 + j;
      sol[i][j] = fl;
    }
  }
}