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
        t = 0;
        s = 0;
#pragma ACCEL PARALLEL reduction=v FACTOR=auto{1}
        for (u = 0; u < 3; u++) {
          s = 0;
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{2}
          for (t = 0; t < 3; t++) {
            for (p = 0; p < 3; p++) {
              s += filter[p][t][u] * orig[r + (-1 + u)][q + (-1 + t)][p];
            }
          }
          v += s;
        }
        sol[r][q][0] = v;
        v = 0;
        t = 0;
        s = 0;
#pragma ACCEL PARALLEL reduction=v FACTOR=auto{1}
        for (u = 0; u < 3; u++) {
          s = 0;
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{1}
          for (t = 0; t < 3; t++) {
            for (p = 1; p < 3; p++) {
              s += filter[p][t][u] * orig[r + (-1 + u)][q + (-1 + t)][p];
            }
          }
          v += s;
        }
        sol[r][q][1] = v;
        v = 0;
        t = 0;
        s = 0;
#pragma ACCEL PARALLEL reduction=v FACTOR=auto{1}
        for (u = 0; u < 3; u++) {
          s = 0;
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{1}
          for (t = 1; t < 3; t++) {
            for (p = 1; p < 3; p++) {
              s += filter[p][t][u] * orig[r + (-1 + u)][q + (-1 + t)][p];
            }
          }
          v += s;
        }
        sol[r][q][2] = v;
      }
    }
  }
//#pragma endscop
}