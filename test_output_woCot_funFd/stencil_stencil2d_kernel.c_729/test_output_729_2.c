#pragma ACCEL kernel

void stencil(double orig[400][400],double sol[400][400],double filter[3][3])
{
  int i;
  int j;
  int k;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 400 - 1; j++) {
      sol[i][j] = 0.0;
      for (k = 0; k < 3; k++) {
        for (y = 0; y < 3; y++) {
          for (x = 0; x < 3; x++) {
            sol[i][j] += filter[k][y] * filter[x][j] * orig[i + (-1 + y)][j + (-1 + x)];
          }
        }
      }
    }
  }
}