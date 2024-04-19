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
  double DX_3;
  double DY_3;
  double DX_4;
  double DY_4;
  double D;
  double C1;
  double C2;
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
  DX_2 = 1.0 / (DX * DX);
  DY_2 = 1.0 / (DY * DY);
  DX_3 = DX_2 / DX;
  DY_3 = DY_2 / DY;
  DX_4 = DX_3 / DX;
  DY_4 = DY_3 / DY;
  D = DX * DY;
  C1 = 1.0 / (2.0 * (DX_2 + DY_2));
  C2 = 1.0 / (2.0 * (DX_4 + DY_4));
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      DY_2 = DY_2 + DY;
      DY_3 = DY_2 / DY;
      DY_4 = DY_3 / DY;
      a = DX_2 * (v[i][0] - 2.0 * v[i][1] + v[i][2]);
      b = DX_3 * (v[i][0] - 2.0 * v[i][1] + v[i][2]) + DY_2 * (u[i][0] - 2.0 * u[i][1] + u[i][2]);
      c = DX_4 * (v[i][0] - 2.0 * v[i][1] + v[i][2]) + DY_3 * (u[i][0] - 2.0 * u[i][1] + u[i][2]) - 2.0 * (q[i][0] - 2.0 * q[i][1] + q[i][2]);
      d = -DX_4 * (u[i][0] - 2.0 * u[i][1] + u[i][2]) - DY_4 * (v[i][0] - 2.0 * v[i][1] + v[i][2]) + 2.0 * (p[i][0] - 2.0 * p[i][1] + p[i][2]);
      tmp = a - d;
      mul1 = tmp * C2;
      mul2 = b * C1;
      p[0][i] = -d + DX_4 * (v[0][i] - 2.0 * v[1][i] + v[2][i]) - 0.5 * (q[0][i] - 2.0 * q[1][i] + q[2][i]) + C1 * (u[0][i] - 2.0 * u[1][i] + u[2][i]);
      q[0][i] = DX_4 * (p[0][i] - p[2][i]) - 0.5 * (v[0][i] - 2.0 * v[1][i] + v[2][i]) + v[1][i];
      p[60][i] = -d + DX_4 * (v[58][i] - 2.0 * v[59][i] + v[0][i]) - 0.5 * (q[58][i] - 2.0 * q[59][i] + q[0][i]) + C1 * (u[58][i] - 2.0 * u[59][i] + u[0][i]);
      q[60][i] = DX_4 * (p[60][i] - p[2][i]) - 0.5 * (v[58][i] - 2.0 * v[59][i] + v[0][i]) + v[59][i];
      for (j = 2; j <= 58; j++) {
        p[j][i] = -mul1 + mul2;
        q[j][i] = DX_4 * (p[j][i] - p[j + 2][i]) - 0.5 * (v[j][i] - 2.0 * v[j + 1][i] + v[j + 2][i]) + v[j + 1][i];
      }
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (i = 1; i < 59; i++) {
      DX_2 = DX_2 + DX;
      DX_3 = DX_2 / DX;
      DX_4 = DX_3 / DX;
      a = DY_2 * (u[0][i] - 2.0 * u[1][i] + u[2][i]);
      b = DY_3 * (u[0][i] - 2.0 * u[1][i] + u[2][i]) + DX_2 * (v[0][i] - 2.0 * v[1][i] + v[2][i]);
      c = DY_4 * (u[0][i] - 2.0 * u[1][i] + u[2][i]) + DX_3 * (v[0][i] - 2.0 * v[1][i] + v[2][i]) - 2.0 * (p[i][0] - 2.0 * p[i][1] + p[i][2]);
      d = -DY_4 * (v[0][i] - 2.0 * v[1][i] + v[2][i]) - DX_4 * (u[0][i] - 2.0 * u[1][i] + u[2][i]) + 2.0 * (q[i][0] - 2.0 * q[i][1] + q[i][2]);
      tmp = a - d;
      mul1 = tmp * C2;
      mul2 = b * C1;
      p[i][0] = -d + DY_4 * (u[i][0] - 2.0 * u[i][1] + u[i][2]) - 0.5 * (p[i][0] - 2.0 * p[i][1] + p[i][2]) + C1 * (v[i][0] - 2.0 * v[i][1] + v[i][2]);
      q[i][0] = DY_4 * (p[i][0] - p[i][2]) -