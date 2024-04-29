#pragma ACCEL kernel

void stencil(int orig[25][20][3],int sol[25][20][3],int filter[9][9][3])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int u;
  int v;
  int f;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  for (r = 1; r < 25 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 1; q < 20 - 1; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 1; p < 3 - 1; p++) {
        for (s = 0; s < 9; s++) {
          for (t = 0; t < 9; t++) {
            for (u = 0; u < 3; u++) {
              f = filter[s][t][u];
              sol[r][q][p] += f * orig[r + (-4 + s)][q + (-4 + t)][p + u];
            }
          }
        }
      }
    }
  }
//#pragma endscop
}