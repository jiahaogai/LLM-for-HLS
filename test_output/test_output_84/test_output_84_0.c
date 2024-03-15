
 #pragma ACCEL kernel

void kernel_mvt(double x[400],double y[400],double u1[400],double u2[400],double v[400],int n)
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    x[i] = ((double )0);
    y[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    for (j = 0; j < 400; j++) {
      x[i] += v[j] * u1[j * 400 + i];
    }
    y[i] = u2[i] * x[i];
  }
}
