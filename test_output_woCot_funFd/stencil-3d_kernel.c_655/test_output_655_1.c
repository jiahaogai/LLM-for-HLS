#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[270][270][270],double sol[270][270][270])
{
  long r;
  long q;
  long p;
  long s;
  long t;
  long u;
  double A;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  for (r = 1; r < 270 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 1; q < 270 - 1; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 1; p < 270 - 1; p++) {
        for (s = 0; s < 3; s++) {
          for (t = 0; t < 3; t++) {
            for (u = 0; u < 3; u++) {
              A = orig[r + s][q + t][p + u];
            }
          }
        }
        sol[r][q][p] = ((A * 4) + (orig[r - 1][q][p] + orig[r + 1][q][p] + orig[r][q - 1][p] + orig[r][q + 1][p] + orig[r][q][p - 1] + orig[r][q][p + 1] + orig[r][q][p])) / 9;
      }
    }
  }
}