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
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  for (r = 1; r < 25 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (q = 1; q < 20 - 1; q++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (p = 1; p < 3 - 1 + 1; p++) {
        v = 0;
        for (s = 0; s < 3; s++) {
          t = 0;
          for (t = 0; t < 3; t++) {
            u = 0;
            for (u = 0; u < 3; u++) {
              v += filter[p][s][t] * orig[r - 1 + s][q - 1 + t][u];
            }
          }
        }
        sol[r][q][p] = v;
      }
    }
  }
//#pragma endscop
}