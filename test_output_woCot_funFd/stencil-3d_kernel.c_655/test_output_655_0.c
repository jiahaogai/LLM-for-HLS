#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[20][20][20],double sol[20][20][20])
{
  long i;
  long j;
  long k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  for (i = 1; i < 20 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 1; j < 20 - 1; j++) {
      for (k = 1; k < 20 - 1; k++) {
        sol[i][j][k] = ((2 * orig[i][j][k]) + (C1 * (orig[i - 1][j][k] + orig[i + 1][j][k] + orig[i][j - 1][k] + orig[i][j + 1][k] + orig[i][j][k - 1] + orig[i][j][k + 1]))) / (C0 * (2 + C1));
      }
    }
  }
//#pragma endscop
}