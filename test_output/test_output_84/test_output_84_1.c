
 #pragma ACCEL kernel

void kernel_mvt(double x[120],double y[120],double u1[120],double u2[120],double v[140])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    x[i] = ((double )0);
    y[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    for (j = 0; j < 140; j++) {
      x[i] += v[j] * u1[j * 120] * u2[i * 120];
      y[i] += v[j] * u1[j * 120];
    }
  }
}
