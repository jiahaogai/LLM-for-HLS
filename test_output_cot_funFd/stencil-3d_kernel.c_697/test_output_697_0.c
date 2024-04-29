#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[27][27][27],double sol[27][27][27])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int u;
  double B0;
  double B1;
  double mul1;
  double mul2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 27; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 27; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{2}
      for (p = 0; p < 27; p++) {
        mul1 = 0.0;
        mul2 = 0.0;
        B0 = 2.0;
        B1 = 1.0;
        for (s = -1; s <= 1; s++) {
          for (t = -1; t <= 1; t++) {
            for (u = -1; u <= 1; u++) {
              mul1 += orig[r + s][q + t][p + u] * B0;
              mul2 += orig[r + s][q + t][p + u] * B1;
            }
          }
        }
        sol[r][q][p] = mul1 - mul2 + 3.0;
      }
    }
  }
}