#pragma ACCEL kernel

void kernel_atax(double A[390][410],double x[410],double y[410],double tmp[390])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 410; i++) {
    tmp[0] += x[i] * A[0][i];
  }
  
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{32}
  for (i = 0; i < 390; i++) {
    y[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{1}
    for (j = 0; j < 410; j++) {
      y[i] += A[i][j] * tmp[j];
    }
  }
}