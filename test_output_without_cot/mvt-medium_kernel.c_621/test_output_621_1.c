- Execute loop iterations concurrently, and apply automatic factor calculation for better resource utilization.

#pragma ACCEL kernel

void kernel_mvt(double x1[400], double x2[400], double y_1[400], double y_2[400], double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double sum = y_1[i];
    for (j = 0; j < 400; j++) {
      sum += A[i][j] * x1[j];
    }
    y_2[i] = sum;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  for (i = 0; i < 400; i++) {
    double sum = y_2[i];
    for (j = 0; j < 400; j++) {
      sum += A[i][j] * x2[j];
    }
    y_1[i] = sum;
  }
}