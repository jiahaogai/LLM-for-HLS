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
  mul1 = B1 * DT / (DX * DX);
  mul2 = B2 * DT / (DY * DY);
  a = -mul1 / 2.0;
  b = 1.0 + a * mul2;
  c = a * mul2 / 2.0;
  d = 1.0 - mul2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_tsteps:
  for (t = 0; t < 40; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_i:
    for (i = 1; i < 59; i++) {
      v[0][i] = 0.0;
      q[i][0] = 0.0;
      loop_j:
      for (j = 1; j < 59; j++) {
        v[i][j] = -d * v[i][j] + u[i][j] * a + v[i][j - 1] * b + v[i][j + 1] * c;
        q[i][j] = -d * q[i][j] + u[i][j] * b + v[i][j - 1] * c + q[i][j + 1] * d;
      }
      v[i][59] = 0.0;
      q[i][59] = 0.0;
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_i_1:
    for (i = 1; i < 59; i++) {
      u[i][0] = 0.0;
      p[i][0] = 0.0;
      loop_j_1:
      for (j = 1; j < 59; j++) {
        u[i][j] = -d * u[i][j] + p[i][j] * a + q[i][j] * b + p[i][j + 1] * c;
        p[i][j] = -d * p[i][j] + p[i][j] * b + q[i][j] * c + u[i][j + 1] * d;
      }
      u[i][59] = 0.0;
      p[i][59] = 0.0;
    }
  }
}