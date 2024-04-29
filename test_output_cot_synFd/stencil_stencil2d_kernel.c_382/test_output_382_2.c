#pragma ACCEL kernel

void stencil(int orig[25][20][3],int sol[25][20][3],int filter[3][3][3])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int u;
  int v;
  int f;
  int g;
  int h;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_r:
  for (r = 1; r < 25 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_q:
    for (q = 1; q < 20 - 1; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_p:
      for (p = 1; p < 3 - 1; p++) {
        loop_s:
        for (s = 0; s < 3; s++) {
          loop_t:
          for (t = 0; t < 3; t++) {
            loop_u:
            for (u = 0; u < 3; u++) {
              f = filter[p][t][u];
              g = orig[r + s][q + t][u];
              h = g * f;
              i = r + s + 1;
              j = q + t + 1;
              sol[i][j][0] += h;
              sol[i][j][1] += h;
              sol[i][j][2] += h;
            }
          }
        }
      }
    }
  }
}