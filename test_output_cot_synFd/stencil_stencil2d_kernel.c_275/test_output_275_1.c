#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[3][3])
{
  int i;
  int j;
  int t;
  int ai[3];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 400 - 1; j++) {
      ai[0] = orig[i - 1][j - 1];
      ai[1] = orig[i - 1][j];
      ai[2] = orig[i - 1][j + 1];
      ai[3] = orig[i][j - 1];
      ai[4] = orig[i][j];
      ai[5] = orig[i][j + 1];
      ai[6] = orig[i + 1][j - 1];
      ai[7] = orig[i + 1][j];
      ai[8] = orig[i + 1][j + 1];
      t = 0;
      t += filter[0][0] * ai[0];
      t += filter[0][1] * ai[1];
      t += filter[0][2] * ai[2];
      t += filter[1][0] * ai[3];
      t += filter[1][1] * ai[4];
      t += filter[1][2] * ai[5];
      t += filter[2][0] * ai[6];
      t += filter[2][1] * ai[7];
      t += filter[2][2] * ai[8];
      sol[i][j] = t;
    }
  }
}