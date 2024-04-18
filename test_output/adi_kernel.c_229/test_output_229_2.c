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
  double e;
  double f;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  DX = 1.0;
  DY = 1.0;
  DT = 1.0;
  B1 = 2.0;
  B2 = 1.0;
  mul1 = B1 * DT / (DX * DX);
  mul2 = B2 * DT / (DY * DY);
  a = -mul1 / 2.0;
  b = 1.0 + a;
  c = mul1 / 2.0;
  d = -mul2 / 2.0;
  e = 1.0 + d;
  f = mul2 / 2.0;
//Column Sweep
  for (j = 1; j < 59; j++) {
//Row Sweep
    for (i = 1; i < 59; i++) {
      u[i][j] = a * (p[i][j] - p[i][j - 1]) + c * (v[i][j] - v[i][j + 1]) + p[i][j];
      v[i][j] = d * (q[i][j] - q[i][j - 1]) + e * (u[i][j] - u[i][j - 1]) + q[i][j];
    }
    v[0][j] = v[1][j];
    v[60][j] = v[59][j];
    u[0][j] = u[1][j];
    u[60][j] = u[59][j];
    q[0][j] = 0.0;
    q[60][j] = 0.0;
    p[0][j] = 0.0;
    p[60][j] = 0.0;
  }
//Row Sweep
  for (i = 1; i < 59; i++) {
    u[i][0] = u[i][1];
    u[i][60] = u[i][59];
    v[i][0] = v[i][1];
    v[i][60] = v[i][59];
    q[i][0] = 0.0;
    q[i][60] = 0.0;
    p[i][0] = 0.0;
    p[i][60] = 0.0;
  }
  u[0][0] = 0.0;
  u[0][60] = 0.0;
  v[0][0] = 0.0;
  v[0][60] = 0.0;
  q[0][0] = 0.0;
  q[0][60] = 0.0;
  p[0][0] = 1.0;
  p[0][60] = 1.0;
}