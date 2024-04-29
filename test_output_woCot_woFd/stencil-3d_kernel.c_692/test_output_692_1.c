#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[20][20][20],long sol[20][20][20])
{
  int t;
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (t = 1; t < 20 - 1; t++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 20 - 1; i++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 20 - 1; j++) {
        for (k = 1; k < 20 - 1; k++) {
          sol[t][i][j][k] = C0 * (orig[t - 1][i][j][k] + orig[t + 1][i][j][k]) + C1 * (orig[t][i - 1][j][k] + orig[t][i + 1][j][k] + orig[t][i][j - 1][k] + orig[t][i][j + 1][k] + orig[t][i][j][k - 1] + orig[t][i][j][k + 1]);
        }
      }
    }
  }
//#pragma endscop
}