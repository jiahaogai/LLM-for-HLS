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
  double DX_6;
  double DY_6;
  double C1;
  double C2;
  double tmp;
  double mul1;
  double mul2;
  double mul3;
  double mul4;
  double a;
  double b;
  double c;
  double d;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  DX = 1.0;
  
#pragma ACCEL TILE FACTOR=auto{1}
  DY = 1.0;
  DX_2 = DX * DX;
  DY_2 = DY * DY;
  DX_4 = DX_2 * DX_2;
  DY_4 = DY_2 * DY_2;
  DX_6 = DX_4 * DX_2;
  DY_6 = DY_4 * DY_2;
  C1 = 3.0 * DX_2 * DY_2;
  C2 = 3.0 * DX_4 * DY_4;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      d = DX_2 * (v[i][0] - 2.0 * v[i][1] + v[i][2]);
      a = 1.0 + C1 * (p[i][0] - 2.0 * p[i][1] + p[i][2]) + DX_4 * (p[i][0] - 2.0 * p[i][1] + p[i][2] - p[i][0] + 4.0 * p[i][1] - 5.0 * p[i][2] + p[i][3]);
      b = 1.0 + C1 * (q[i][0] - 2.0 * q[i][1] + q[i][2]) + DX_4 * (q[i][0] - 2.0 * q[i][1] + q[i][2] - q[i][0] + 4.0 * q[i][1] - 5.0 * q[i][2] + q[i][3]);
      c = p[i][0] - 2.0 * p[i][1] + p[i][2];
      mul1 = a * u[i][0] + b * u[i][1] + d * u[i][2];
      mul2 = a * v[i][0] + b * v[i][1] + d * v[i][2];
      mul3 = a * p[i][0] + b * p[i][1] + d * p[i][2];
      mul4 = a * q[i][0] + b * q[i][1] + d * q[i][2];
      u[i][0] = mul1 + C2 * (v[i][0] - 2.0 * v[i][1] + v[i][2]) * c;
      v[i][0] = mul2 + C2 * (-p[i][0] + 2.0 * p[i][1] - p[i][2]) * c;
      p[i][0] = mul3 + DX_6 * (p[i][0] - 2.0 * p[i][1] + p[i][2]) * (v[i][0] - 2.0 * v[i][1] + v[i][2]);
      q[i][0] = mul4 + DX_6 * (q[i][0] - 2.0 * q[i][1] + q[i][2]) * (v[i][0] - 2.0 * v[i][1] + v[i][2]);
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (j = 1; j < 59; j++) {
      d = DY_2 * (u[0][j] - 2.0 * u[1][j] + u[2][j]);
      a = 1.0 + C1 * (p[0][j] - 2.0 * p[1][j] + p[2][j]) + DY_4 * (p[0][j] - 2.0 * p[1][j] + p[2][j] - p[0][j] + 4.0 * p[1][j] - 5.0 * p[2][j] + p[3][j]);
      b = 1.0 + C1 * (q[0][j] - 2.0 * q[1][j] + q[2][j]) + DY_4 * (q[0][j] - 2.0 * q[1][j] + q[2][j] - q[0][j] + 4.0 * q[1][j] - 5.0 * q[2][j] + q[3][j]);
      c = p[0][j] - 2.0 * p[1][j] + p[2][j];
      mul1 = a * u[0][j] + b * u[1][j] + d * u[2][j];
      mul2 = a * v[0][j] + b * v[1][j] + d * v[2][j];
      mul3 = a * p[0][j] + b * p[1][j] + d * p[2][j];
      mul4 = a * q[0][j] + b * q[1][j] + d * q[2][j];
      u[0][j] = mul1 + C2 * (v[0][j] - 2.0 * v[1][j] + v[2][j]) * c;
      v[0][j] = mul2 + C2 * (-p[0][j] + 2.0 * p[1][j] - p[2][j]) * c;
      p[0][j] = mul3 + DY_6 * (p[0][j] - 2.0 * p[1][j] + p[2][j]) * (v[0][j] - 2.0 * v[1][j] + v[2][j]);
      q[0][j] = mul4 + DY_6 * (q[0][j] - 2.0 * q[1][j] + q[2][j]) * (v[0][j] - 2.0 * v[1][j] + v[2][j]);
    }
  }
//Sweep 1
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  for (i = 1; i < 59; i++) {
    d