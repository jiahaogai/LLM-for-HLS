#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[2][2])
{
  int i;
  int j;
  int fl;
  int row;
  int col;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 3; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 3; j++) {
      fl = filter[0][0] * orig[i - 1][j - 1];
      fl += filter[1][0] * orig[i - 1][j];
      fl += filter[0][1] * orig[i][j - 1];
      fl += filter[1][1] * orig[i][j];
      sol[i][j] = fl;
    }
  }
//#pragma endscop
}