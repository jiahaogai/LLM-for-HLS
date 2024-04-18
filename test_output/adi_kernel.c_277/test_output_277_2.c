#pragma ACCEL kernel

void kernel_adi(int tsteps,int n,double u[60][60],double v[60][60],double p[60][60],double q[60][60])
{
  int t;
  int i;
  int j;
  double DX;
  double DY;
  double DX_2;
  double DY_2;
  double DX_4;
  double DY_4;
  double tmp;
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
  DX_2 = DX * DX;
  DY_2 = DY * DY;
  DX_4 = DX_2 * DX_2;
  DY_4 = DY_2 * DY_2;
  u[0][0] = 5.0;
  u[0][1] = 0.0;
  u[0][2] = 0.0;
  u[1][0] = -1.0;
  u[1][1] = 5.0;
  u[1][2] = 0.0;
  u[2][0] = 0.0;
  u[2][1] = -1.0;
  u[2][2] = 5.0;
  v[0][0] = 1.0;
  v[0][1] = 0.5;
  v[0][2] = -0.5;
  v[1][0] = 0.5;
  v[1][1] = 1.0;
  v[1][2] = -0.5;
  v[2][0] = -0.5;
  v[2][1] = 0.5;
  v[2][2] = 1.0;
  p[0][0] = 1.0;
  p[0][1] = 0.5;
  p[0][2] = 0.5;
  p[1][0] = 0.5;
  p[1][1] = 1.0;
  p[1][2] = 0.5;
  p[2][0] = 0.5;
  p[2][1] = 0.5;
  p[2][2] = 1.0;
  q[0][0] = 0.5;
  q[0][1] = 0.5;
  q[0][2] = 0.5;
  q[1][0] = 0.5;
  q[1][1] = 0.5;
  q[1][2] = 0.5;
  q[2][0] = 0.5;
  q[2][1] = 0.5;
  q[2][2] = 0.5;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_tsteps:
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_i:
    for (i = 1; i < 59; i++) {
      tmp = DX_4 * (u[i - 1][0] - 2.0 * u[i][0] + u[i + 1][0]);
      mul1 = tmp + DY_4 * (v[i][0 - 1] - 2.0 * v[i][0] + v[i][0 + 1]);
      a = p[i][0] + DX_2 * (q[i - 1][0] - 2.0 * q[i][0] + q[i + 1][0]) + DY_2 * (u[i][0 - 1] - 2.0 * u[i][0] + u[i][0 + 1]);
      b = p[i][39] + DX_2 * (q[i - 1][39] - 2.0 * q[i][39] + q[i + 1][39]) + DY_2 * (u[i][39 - 1] - 2.0 * u[i][39] + u[i][39 + 1]);
      c = p[i][38] + DX_2 * (q[i - 1][38] - 2.0 * q[i][38] + q[i + 1][38]) + DY_2 * (u[i][38 - 1] - 2.0 * u[i][38] + u[i][38 + 1]);
      d = a + (b - c) + mul1;
      q[i][0] = -d / ((DX_2 * (v[i][39] - 2.0 * v[i][0] + v[i][38])) / DY_2);
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 59; j++) {
      tmp = DY_4 * (u[0][j - 1] - 2.0 * u[0][j] + u[0][j + 1]);
      mul2 = tmp + DX_4 * (v[j - 1][0] - 2.0 * v[j][0] + v[j + 1][0]);
      a = p[0][j] + DX_2 * (q[0][j - 1] - 2.0 * q[0][j] + q[0][j + 1]) + DY_2 * (u[0][j - 1] - 2.0 * u[0][j] + u[0][j + 1]);
      b = p[39][j] + DX_2 * (q[39][j - 1] - 2.0 * q[39][j] + q[39][j + 1]) + DY_2 * (u[39][j - 1] - 2.0 * u[39][j] + u[39][j + 1]);
      c = p[38][j] + DX_2 * (q[38][j - 1] - 2.0 * q[38][j] + q[38][j + 1]) + DY_2 * (u[38][j - 1] - 2.0 * u[38][j] + u[38][j + 1]);
      d = a + (b - c) + mul2;
      q[39][j] = -d / ((DY_2 * (v[39][j + 1] - 2.0 * v[39][j] + v[39][j - 1])) / DX_2);
    }
  }
}