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
        v = 0;
        for (i = -1; i <= 1; i++) {
          u = 0;
          for (j = -1; j <= 1; j++) {
            for (k = -1; k <= 1; k++) {
              v += filter[i + 1][j + 1][k + 1] * orig[r + i][q + j][p + k];
              u += filter[i + 1][j + 1][k + 1];
            }
          }
          sol[r][q][p] = v / ((double )u);
        }
      }
    }
  }
//#pragma endscop
}