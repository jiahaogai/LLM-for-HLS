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
    for (z = 1; z < 20 - 1; z++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (y = 1; y < 20 - 1; y++) {
        for (x = 1; x < 20 - 1; x++) {
          sol[t][z][y][x] = ((orig[t - 1][z][y][x] + orig[t + 1][z][y][x]) * (orig[t][z - 1][y][x] + orig[t][z + 1][y][x]) * (orig[t][z][y - 1][x] + orig[t][z][y + 1][x]) * (orig[t][z][y][x - 1] + orig[t][z][y][x + 1])) / (C0 * C1 * 8.0);
        }
      }
    }
  }
//#pragma endscop
}