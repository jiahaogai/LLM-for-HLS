c
 #pragma ACCEL kernel

void kernel_atax(double A[390][410],double x[410],double y[410],double tmp[390])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  gemv_1:
  for (i = 0; i < 410; i++) {
    tmp[0] = A[0][i] * x[i];
    gemv_2:
    for (j = 1; j < 390; j++) {
      tmp[j] = A[j][i] * x[i] + tmp[j - 1];
    }
    gemv_3:
    for (j = 0; j < 410; j++) {
      y[j] = tmp[389] * A[389][j] + y[j];
    }
  }
}