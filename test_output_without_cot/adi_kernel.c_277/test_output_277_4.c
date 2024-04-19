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
//Column Sweep
  for (j = 1; j < 59; j++) {
//Row Sweep
    for (i = 1; i < 59; i++) {
      v[i][j] = -1.0 * (u[i][j + 1] - u[i][j - 1]) / DX + 2.0 * (u[i + 1][j] - u[i - 1][j]) / (DX * DX) - 1.0 * (u[i][j + 1] - u[i][j - 1]) / DY + 2.0 * (u[i][j + 1] - u[i][j - 1]) / (DY * DY);
    }
  }
//Column Sweep
  for (j = 1; j < 59; j++) {
//Row Sweep
    for (i = 1; i < 59; i++) {
      u[i][j] = a * (d * v[i][j] - b * (v[i + 1][j] + v[i - 1][j])) - c * (p[i][j] - q[i][j]);
    }
  }
}