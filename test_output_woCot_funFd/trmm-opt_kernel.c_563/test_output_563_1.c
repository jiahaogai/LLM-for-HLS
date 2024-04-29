#pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double sum;
  for (i = 0; i < 60; i++) {
     for (j = 0; j < 80; j++) {
        sum = 0.0;
        for (k = 0; k < 60; k++) {
          sum += alpha * A[i][k] * B[k][j];
        }
        B[i][j] = sum;
     }
  }
}