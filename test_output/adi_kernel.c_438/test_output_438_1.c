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
  DX = 1.0 / ((double )60);
  
#pragma ACCEL TILE FACTOR=auto{1}
  DY = 1.0 / ((double )60);
  DX_2 = DX * DX;
  DY_2 = DY * DY;
  DX_4 = DX_2 * DX_2;
  DY_4 = DY_2 * DY_2;
  DX_6 = DX_4 * DX_2;
  DY_6 = DY_4 * DY_2;
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (t = 1; t <= 40; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      a = DX_2 * (v[i + 1][0] - 2.0 * v[i][0] + v[i - 1][0]);
      b = DY_2 * (u[0][i + 1] - 2.0 * u[0][i] + u[0][i - 1]);
      c = a + b;
      d = DX_4 * (v[i + 1][1] - 2.0 * v[i][1] + v[i - 1][1]) - DY_4 * (u[1][i + 1] - 2.0 * u[1][i] + u[1][i - 1]);
      mul1 = c + d;
      tmp = - DX_6 * (v[i + 1][2] - 2.0 * v[i][2] + v[i - 1][2]) + DY_6 * (u[2][i + 1] - 2.0 * u[2][i] + u[2][i - 1]);
      mul2 = mul1 + tmp;
      p[0][i] = mul2 + j;
      q[i][0] = p[0][i];
      mul3 = DX_4 * (v[i + 1][3] - 2.0 * v[i][3] + v[i - 1][3]) - DY_4 * (u[3][i + 1] - 2.0 * u[3][i] + u[3][i - 1]);
      mul4 = mul3 + c;
      u[i][0] = mul4 + v[i][0];
      v[i][0] = p[0][i];
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (j = 1; j < 59; j++) {
      a = DX_2 * (v[0][j + 1] - 2.0 * v[0][j] + v[0][j - 1]);
      b = DY_2 * (u[j + 1][0] - 2.0 * u[j][0] + u[j - 1][0]);
      c = a + b;
      d = DX_4 * (v[1][j + 1] - 2.0 * v[1][j] + v[1][j - 1]) - DY_4 * (u[j + 1][1] - 2.0 * u[j][1] + u[j - 1][1]);
      mul1 = c + d;
      tmp = - DX_6 * (v[2][j + 1] - 2.0 * v[2][j] + v[2][j - 1]) + DY_6 * (u[j + 1][2] - 2.0 * u[j][2] + u[j - 1][2]);
      mul2 = mul1 + tmp;
      p[j][0] = mul2 + u[j][0];
      q[0][j] = p[j][0];
      mul3 = DX_4 * (v[3][j + 1] - 2.0 * v[3][j] + v[3][j - 1]) - DY_4 * (u[j + 1][3] - 2.0 * u[j][3] + u[j - 1][3]);
      mul4 = mul3 + c;
      v[j][0] = mul4 + v[j][0];
      u[j][0] = q[0][j];
    }
  }
}