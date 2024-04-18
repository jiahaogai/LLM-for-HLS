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
  c = 1.0 + 2.0 * mul2 / (mul1 + mul2);
  d = 1.0 + 2.0 * mul1 / (mul1 + mul2);
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      v[0][i] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = v[0][i];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 59; j++) {
        p[i][j] = -a * (p[i][j - 1] + p[i][1 + j]) + u[i][j];
        q[i][j] = -b * (q[i][j - 1] + q[i][1 + j]) + v[i][j];
      }
      d = d - 1.0;
      v[60 - 1][i] = 1.0 / d;
      u[i][60 - 1] = p[i][60 - 1] + q[i][60 - 1] * v[60 - 1][i];
      for (j = 60 - 2; j >= 1; j--) {
        u[i][j] = p[i][j] + q[i][j] * v[j][i] + u[i][j + 1];
      }
      a = a + c;
      b = b + d;
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      u[i][0] = 0.0;
      q[i][0] = 1.0;
      p[0][i] = 0.0;
      u[i][60 - 1] = p[i][60 - 1] + q[i][60 - 1] * v[60 - 1][i];
      for (j = 1; j < 60 - 1; j++) {
        q[i][j] = -d * q[i][j] + u[i][j + 1] - p[i][j - 1] + q[i][j - 1] * v[j][i];
      }
      p[i][60 - 1] = 1.0 / d * (u[i][60 - 1] - q[i][60 - 1] * v[60 - 1][i]);
      for (j = 58; j >= 1; j--) {
        u[i][j] = p[i][j] + q[i][j] * v[j][i] + u[i][j - 1];
      }
      d = d + 1.0;
      a = a + c;
      b = b + d;
    }
  }
}