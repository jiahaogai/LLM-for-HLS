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
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (i = 0; i < 60; i++) {
      x[t] += u[i][t] * v[i][t];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (t = 0; t <= 79; t++) {
    y[t] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (j = 0; j < 60; j++) {
      y[t] += w[j][t] * x[j];
    }
    z[t] = y[t] + z[t];
  }
}