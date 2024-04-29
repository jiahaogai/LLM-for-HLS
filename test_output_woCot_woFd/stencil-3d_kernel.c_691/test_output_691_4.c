#pragma ACCEL kernel

void stencil3d(long C0,long C1)
{
  long i;
  long j;
  long k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 1; i < 4; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 4; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 1; k < 4; k++) {
        sol[i][j][k] = 0.125 * ((((2.0 * sol[i - 1][j][k]) + (2.0 * sol[i + 1][j][k])) + (2.0 * sol[i][j - 1][k])) + (2.0 * sol[i][j + 1][k])) + 0.125 * ((((2.0 * sol[i - 1][j][k - 1]) + (2.0 * sol[i + 1][j][k - 1])) + (2.0 * sol[i - 1][j][k + 1])) + (2.0 * sol[i + 1][j][k + 1])) + sol[i][j][k];
      }
    }
  }
//#pragma endscop
}