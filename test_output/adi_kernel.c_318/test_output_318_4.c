#pragma ACCEL kernel

void kernel_adi(int tsteps,int n,double u[60][60],double v[60][60],double p[60][60],double q[60][60])
{
  int t;
  int i;
  int j;
  double DX;
  double DY;
  double DT;
  double B1;
  double B2;
  double mul1;
  double mul2;
  double a;
  double b;
  double c;
  double d;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  DX = 1.0;
  DY = 1.0;
  DT = 1.0;
  B1 = 2.0;
  B2 = 1.0;
  mul1 = B1 * DX * DX;
  mul2 = B2 * DY * DY;
  a = -mul1 / (mul1 + mul2);
  b = -mul2 / (mul1 + mul2);
  c = 1.0 + 2.0 * mul1 / (mul1 - mul2);
  d = 1.0 + 2.0 * mul2 / (mul1 - mul2);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_tsteps:
  for (t = 0; t < 40; t++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j2:
    for (j = 1; j < 59; j++) {
      loop_i2:
      for (i = 1; i < 59; i++) {
        u[i][j] = a * (p[i][j] - p[i][j - 1]) - b * (q[i][j] - q[i][j - 1]) ;
        v[i][j] = c * (p[i][j] - p[i - 1][j]) - d * (q[i][j] - q[i - 1][j]) ;
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    loop_j1:
    for (j = 0; j < 60; j++) {
      loop_i1:
      for (i = 0; i < 60; i++) {
        p[i][j] = 0.25 * (u[i][j] + u[i][j + 1] + v[i][j] + v[i + 1][j]);
      }
    }
  }
}