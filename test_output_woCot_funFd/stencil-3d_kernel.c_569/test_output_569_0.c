#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[27][27][27],double sol[27][27][27])
{
  long i;
  long j;
  long k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  for (i = 1; i < 27 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 1; j < 27 - 1; j++) {
      for (k = 1; k < 27 - 1; k++) {
        sol[i][j][k] = ((2 * orig[i][j][k]) + (orig[i - 1][j][k] + orig[i + 1][j][k] + orig[i][j - 1][k] + orig[i][j + 1][k] + orig[i][j][k - 1] + orig[i][j][k + 1]) + (-5 * orig[i][j][k])) / 4;
      }
    }
  }
//#pragma endscop
}