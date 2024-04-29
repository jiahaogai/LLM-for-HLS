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
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 0; p < 27; p++) {
        mul1 = 0.0;
        mul2 = 0.0;
        B0 = orig[r][q][p];
        B1 = orig[r][q][p + 1];
#pragma ACCEL PARALLEL FACTOR=auto{8}
        for (s = 0; s < 27; s++) {
#pragma ACCEL PARALLEL FACTOR=auto{2}
          for (t = 0; t < 27; t++) {
            for (u = 0; u < 27; u++) {
              mul1 += B0 * orig[r][s][t] * orig[q][u][p];
              mul2 += B1 * orig[r][s][t] * orig[q][u][p + 1];
            }
          }
        }
        sol[r][q][p] = mul1 + mul2;
      }
    }
  }
}