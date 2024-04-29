#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[20][20][20],double sol[20][20][20])
{
  int t;
  int x;
  int y;
  int z;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  for (t = 1; t < 20 - 1; t++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (x = 1; x < 20 - 1; x++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (y = 1; y < 20 - 1; y++) {
        for (z = 1; z < 20 - 1; z++) {
          sol[t][x][y][z] = ((orig[t - 1][x][y][z] + orig[t + 1][x][y][z]) * (orig[t][x - 1][y][z] + orig[t][x + 1][y][z]) * (orig[t][x][y - 1][z] + orig[t][x][y + 1][z]) * (orig[t][x][y][z - 1] + orig[t][x][y][z + 1])) / (C0 * C1 * 8.0);
        }
      }
    }
  }
//#pragma endscop
}