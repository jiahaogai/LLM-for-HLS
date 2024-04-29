#pragma ACCEL kernel

void stencil(int orig[25][20][30],int sol[25][20][30],int filter[9][9][30])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int u;
  int v;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 1; r < 25 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 1; q < 20 - 1; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 1; p < 30 - 1; p++) {
        v = 0;
        int t_min = (r - 1) * 20 * 30 + (q - 1) * 30 + p - 1;
        int t_max = (r - 1) * 20 * 30 + (q - 1) * 30 + p + 1;
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (t = t_min; t <= t_max; t++) {
          int u_min = (s - 1) * 30 + p - 1;
          int u_max = (s - 1) * 30 + p + 1;
#pragma ACCEL PARALLEL reduction=v FACTOR=auto{1}
          for (u = u_min; u <= u_max; u++) {
            v += filter[s][t][u] * orig[r][q][u];
          }
        }
        sol[r][q][p] = v;
      }
    }
  }
//#pragma endscop
}