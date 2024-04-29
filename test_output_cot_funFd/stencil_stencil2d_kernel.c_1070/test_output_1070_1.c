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
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 0; p < 30; p++) {
        sol[r][q][p] = 0.0;
        for (i = -4; i <= 4; i++) {
          s = r + i;
          if (s < 0) {
            s = 0;
          }
          else {
            if (s > 24) {
              s = 24;
            }
          }
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          for (j = -4; j <= 4; j++) {
            t = q + j;
            if (t < 0) {
              t = 0;
            }
            else {
              if (t > 19) {
                t = 19;
              }
            }
            
#pragma ACCEL PIPELINE auto{off}
            
#pragma ACCEL TILE FACTOR=auto{1}
            for (k = -4; k <= 4; k++) {
              u = p + k;
              if (u < 0) {
                u = 0;
              }
              else {
                if (u > 29) {
                  u = 29;
                }
              }
              v = k + 4;
              sol[r][q][p] += filter[i + 4][j + 4][v] * orig[s][t][u];
            }
          }
        }
      }
    }
  }
//#pragma endscop
}