#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[20][20][20],long sol[20][20][20])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int u;
  long mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 1; r < 20 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 1; q < 20 - 1; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 1; p < 20 - 1; p++) {
        for (s = 0; s < 3; s++) {
          for (t = 0; t < 3; t++) {
            for (u = 0; u < 3; u++) {
              mult = C0;
              mult = mult * (orig[r + s][q + t][p + u]);
            }
          }
        }
        sol[r][q][p] = mult;
      }
    }
  }
}