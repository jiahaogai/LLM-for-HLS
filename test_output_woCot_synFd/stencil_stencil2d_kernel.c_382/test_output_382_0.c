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
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 1; r < 25 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (q = 1; q < 20 - 1; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (p = 1; p < 30 - 1; p++) {
        v = 0;
        for (t = -1; t <= 1; t++) {
          s = 0;
          for (u = -1; u <= 1; u++) {
            s += filter[t + 1][u + 1][p] * orig[r + t][q][p + u];
          }
          v += s;
        }
        sol[r][q][p] = v;
      }
    }
  }
//#pragma endscop
}