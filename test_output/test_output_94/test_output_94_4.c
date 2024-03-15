
 #pragma ACCEL kernel

void kernel_correlation(double float_n,double data[100][80],double corr[80][80],double k[80])
{
  int i;
  int j;
  int k_col;
  double tmp;
  double sum_v;
  double mul_v;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_j:
  for (j = 0; j < 80; j++) {
    loop_k:
    for (k_col = 0; k_col < 80; k_col++) {
      tmp = ((double )0);
      sum_v = k[k_col] * ((double )1.0E+20);
      loop_i:
      for (i = 0; i < 100; i++) {
        mul_v = data[i][j] * k[k_col];
        tmp += mul_v;
        sum_v += mul_v;
      }
      corr[j][k_col] = tmp / sum_v;
    }
  }
}
