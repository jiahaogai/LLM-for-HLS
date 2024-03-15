
 #pragma ACCEL kernel

void kernel_adi(int tsteps,int n,double u[60][60],double v[60][60],double p[60][60],double q[60][60],double r[60][60],double s[60][60])
{
  int t;
  int i;
  int j;
  double DX;
  double DY;
  double DX2;
  double DY2;
  double DXDY;
  double C1;
  double C2;
  double C3;
  double C4;
  double C5;
  double tmp;
  double mul1;
  double mul2;
  double mul3;
  double mul4;
  double mul5;
  double a;
  double b;
  double c;
  double d;
  double e;
  double f;

//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  DX = 1.0 / ((double )60);
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  DY = 1.0 / ((double )60);
  DX2 = DX * DX;
  DY2 = DY * DY;
  DXDY = DX2 * DY;
  C1 = 3.0 * DX2 * DY2;
  C2 = 3.0 * DX2 - 2.0 * DXDY - DY2;
  C3 = 3.0 * DXDY - 2.0 * DX2 * DY;
  C4 = DX2 - DY2;
  C5 = -2.0 * DX2 * DY;
//#pragma ACCEL PIPELINE auto{off}
//#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 39; t++) {
//#pragma ACCEL PIPELINE auto{off}
//#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      for (j = 1; j < 59; j++) {
        tmp = C1 * (u[i - 1][j] + u[i + 1][j]) + C2 * (u[i][j - 1] + u[i][j + 1]) + C3 * (u[i][j]) + C4 * (v[i - 1][j] + v[i + 1][j]) + C5 * (v[i][j - 1] + v[i][j + 1]) - DX2 * p[i][j] - DY2 * q[i][j];
        a = DX * (v[i][j] - v[i - 1][j]) - DY * (u[i][j] - u[i][j - 1]);
        b = -DX * (v[i + 1][j] - v[i][j]) - DY * (u[i][j + 1] - u[i][j]);
        c = DX * (v[i][j + 1] - v[i][j]) - DY * (u[i + 1][j] - u[i][j]);
        d = DX * (u[i][j] - u[i - 1][j]) - DY * (v[i][j] - v[i - 1][j]);
        e = tmp + C1 * a * d - C2 * b * d - C3 * c * a - C4 * b * c + C5 * (p[i][j] - p[i - 1][j] - q[i][j] + q[i - 1][j]);
        f = 1.0 / (C2 * d - C1 * b);
        p[i][j] = f * (C2 * e - C1 * c * d);
        q[i][j] = f * (c * a - d * b - e);
        r[i][j] = u[i][j] - DX2 * p[i][j] - DY2 * q[i][j];
        s[i][j] = v[i][j] - DX * p[i][j] - DY * q[i][j];
      }
    }
//#pragma ACCEL PIPELINE auto{__PIPE__L1}
  }
//#pragma endscop
}
