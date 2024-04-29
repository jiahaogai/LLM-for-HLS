#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[390][390][390],double sol[32][32][32])
{
  long r;
  long q;
  long p;
  long s;
  long t;
  long u;
  double beta;
  double fr;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  for (r = 1; r < 390 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 1; q < 390 - 1; q++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 1; p < 390 - 1; p++) {
        for (s = 0; s < 32; s++) {
          for (t = 0; t < 32; t++) {
            for (u = 0; u < 32; u++) {
              beta = 1.0 / ((((double )0)) + ((orig[r - 1][q][p] + orig[r + 1][q][p] + orig[r][q - 1][p] + orig[r][q + 1][p] + orig[r][q][p - 1] + orig[r][q][p + 1] + orig[r][q][p]) * 0.125));
              fr = orig[r][q][p] * beta;
              sol[s][t][u] += fr;
            }
          }
        }
      }
    }
  }
}