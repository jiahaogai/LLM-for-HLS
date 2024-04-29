#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[390][390][390],double sol[32][32][32])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  double value;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_k:
/* Standardize from: for(k = 1; k < 390 - 1; k++) {...} */
  for (k = 1 + 0; k <= 390 - 1 + 0; k++) {
     k_col = k;
     loop_j:
/* Standardize from: for(j = 1; j < 390 - 1; j++) {...} */
    for (j = 1 + 0; j <= 390 - 1 + 0; j++) {
      j_col = j;
      loop_i:
/* Standardize from: for(i = 1; i < 390 - 1; i++) {...} */
      for (i = 1 + 0; i <= 390 - 1 + 0; i++) {
        i_col = i;
        value = ((orig[i_col][j_col][k_col] + orig[i_col][j_col][k_col - 1]) + orig[i_col][j_col][k_col + 1]) + (orig[i_col][j_col - 1][k_col] + orig[i_col][j_col + 1][k_col]) + orig[i_col][j_col][k_col];
        sol[i / 32][j / 32][k / 32] = value / 6.0;
      }
    }
  }
}