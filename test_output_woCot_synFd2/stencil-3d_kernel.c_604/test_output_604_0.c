#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[2][2][2],long sol[2][2][2])
{
  long i;
  long j;
  long k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 1; i < 2; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (j = 1; j < 2; j++) {
      for (k = 1; k < 2; k++) {
        sol[i][j][k] = ((orig[i - 1][j][k] + orig[i + 1][j][k]) + (orig[i][j - 1][k] + orig[i][j + 1][k])) + (orig[i][j][k - 1] + orig[i][j][k + 1]);
      }
    }
  }
//#pragma endscop
}