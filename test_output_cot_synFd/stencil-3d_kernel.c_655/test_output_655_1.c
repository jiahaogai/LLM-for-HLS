#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[27],double sol[27])
{
  double C2;
  long i;
  long j;
  long k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  for (i = 1; i < 27 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 1; j < 27 - 1; j++) {
      for (k = 1; k < 27 - 1; k++) {
        C2 = ((double )0);
#pragma ACCEL PARALLEL reduction=C2 FACTOR=auto{3}
        for (long r = -1; r <= 1; r++) {
#pragma ACCEL PARALLEL reduction=C2 FACTOR=auto{3}
          for (long s = -1; s <= 1; s++) {
#pragma ACCEL PARALLEL reduction=C2 FACTOR=auto{3}
            for (long t = -1; t <= 1; t++) {
              C2 += ((double )(r * s * t)) * orig[i + r][j + s][k + t];
            }
          }
        }
        sol[i][j][k] = C0 * C1 * C2;
      }
    }
  }
//#pragma endscop
}