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
//#pragma scop
  DX = 1.0 / ((double )60);
  DY = 1.0 / ((double )60);
  DT = 1.0 / ((double )40);
  B1 = 2.0;
  B2 = 1.0;
  mul1 = B1 * DT / (DX * DX);
  mul2 = B2 * DT / (DY * DY);
  a = -mul1 / 2.0;
  b = 1.0 + mul1;
  c = a;
  d = -mul2 / 2.0;
  e = 1.0 + mul2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      v[0][i] = 1.0;
      u[i][0] = 0.0;
      a = mul1 * v[0][i];
      d = mul2 * p[i][0];
      b = v[0][i] - a;
      c = u[i][0] - d;
      for (j = 1; j < 59; j++) {
        v[j][i] = b * v[j][i] - c * u[j][i];
        u[i][j] = a * u[j][i] + b * u[i][j] - d * v[i][j];
      }
      v[60][i] = 1.0;
      u[i][60] = 0.0;
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      p[0][i] = 1.0;
      q[i][0] = 0.0;
      a = mul1 * p[i][0];
      d = mul2 * u[0][i];
      b = p[i][0] - a;
      c = q[i][0] - d;
      for (j = 1; j < 59; j++) {
        p[j][i] = b * p[j][i] - c * q[j][i];
        q[i][j] = a * q[j][i] + b * q[i][j] - d * p[i][j];
      }
      p[60][i] = 1.0;
      q[i][60] = 0.0;
    }
  }
//#pragma endscop
}