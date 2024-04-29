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
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{2}
      for (p = 0; p < 3; p++) {
        
#pragma ACCEL PIPELINE auto{flatten}
        
#pragma ACCEL TILE FACTOR=auto{1}
        for (s = 0; s < 3; s++) {
          v = s + 1 - 1;
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          for (t = 0; t < 3; t++) {
            u = t + 1 - 1;
            sol[r][q][p] += filter[p][s][t] * orig[r][q + v][u];
          }
        }
      }
    }
  }
//#pragma endscop
}