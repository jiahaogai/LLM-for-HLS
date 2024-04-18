#pragma ACCEL kernel

void kernel_mvt(int tsteps,int n,double u[60][60],double v[60][60],double w[60][60],double x[60],double y[60],double z[80])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t <= 79; t++) {
    z[t] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t <= 79; t++) {
    x[t] = 0.0;
    y[t] = 0.0;
    for (i = 0; i < 60; i++) {
      
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{__PARA__L2}
      for (j = 0; j < 60; j++) {
        x[t] = x[t] + u[i][j] * v[j][t];
      }
    }
    for (i = 0; i < 60; i++) {
      y[t] = y[t] + u[i][60] * x[i];
    }
    for (i = 0; i < 60; i++) {
      z[t] = z[t] + y[i] * w[i][t];
    }
  }
}