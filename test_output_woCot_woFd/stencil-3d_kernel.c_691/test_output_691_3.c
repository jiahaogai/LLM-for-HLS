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
        sol[i][j][k] = 0.125 * ((((2 * C0[i][j][k]) + (C1[i][j][k - 1])) + (C1[i][j][k + 1])) + (((2 * C1[i][j][k]) + (C0[i][j][k - 1])) + (C0[i][j][k + 1])));
      }
    }
  }
//#pragma endscop
}