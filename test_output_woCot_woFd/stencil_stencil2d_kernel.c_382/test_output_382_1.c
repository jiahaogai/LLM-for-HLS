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
  int i;
  int j;
  int k;
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
      for (p = 1; p < 3 - 1; p++) {
        v = 1;
        t = r - 1;
        while (t <= r + 1) {
          s = q - 1;
          while (s <= q + 1) {
            u = p - 1;
            while (u <= p + 1) {
              i = t - 1;
              j = s - 1;
              k = u - 1;
              sol[r][q][p] += filter[v][i][j] * orig[i][j][k];
              u++;
            }
            s++;
          }
          t++;
          v++;
        }
      }
    }
  }
//#pragma endscop
}