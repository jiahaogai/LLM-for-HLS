#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[390][390][390],double sol[32][32][32])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  double mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_k:
  for (k = 1; k < 390 - 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 390 - 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
      for (i = 1; i < 390 - 1; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        mul = -0.5 * orig[i][j][k];
        sol[i][j][k] = mul * (orig[i_col][j_col][k_col] + orig[i_col][j_col][k + 1] + orig[i_col][j + 1][k_col] + orig[i_col][j + 1][k + 1] + orig[i + 1][j_col][k_col] + orig[i + 1][j_col][k + 1] + orig[i + 1][j + 1][k_col] + orig[i + 1][j + 1][k + 1]);
      }
    }
  }
}