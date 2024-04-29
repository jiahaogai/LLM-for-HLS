#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[25][25][25],long sol[25][25][25])
{
  long i;
  long j;
  long k;
  long ko;
  long kd;
  long jd;
  long i_col;
  long j_col;
  long k_col;
  long sum0;
  long sum1;
  long mul0;
  long mul1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 25 - 1; j++) {
      for (k = 1; k < 25 - 1; k++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        sum0 = ((orig[i_col][j_col][k_col] + orig[i_col][j_col][k + 1]) + orig[i_col][j_col][k - 1]) + ((orig[i_col][j - 1][k_col] + orig[i_col][j + 1][k_col]) + orig[i_col][j - 1][k + 1]) + orig[i_col][j + 1][k + 1] + orig[i_col][j + 1][k - 1] + orig[i_col][j - 1][k - 1] + orig[i_col][j][k];
        sum1 = ((orig[i][j_col][k_col] + orig[i][j_col][k + 1]) + orig[i][j_col][k - 1]) + ((orig[i][j + 1][k_col] + orig[i][j - 1][k_col]) + orig[i][j + 1][k + 1]) + orig[i][j - 1][k + 1] + orig[i][j - 1][k - 1] + orig[i][j + 1][k - 1] + orig[i][j][k];
        mul0 = sum0 * C0;
        mul1 = sum1 * C1;
        sol[i][j][k] = mul0 + mul1;
      }
    }
  }
}