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
  f = d;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i <= 58; i++) {
      v[0][i] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = v[0][i];
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (j = 1; j <= 58; j++) {
        p[i][j] = -a * p[i][j - 1] - d * p[j - 1][i] + u[i][j];
        q[i][j] = -b * q[i][j - 1] - e * q[j - 1][i] + v[i][j];
        u[i][j] = p[i][j] - d * (q[i][j] - f * u[j][i]);
        v[i][j] = q[i][j] - e * (u[i][j] - b * v[j][i]);
      }
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i <= 58; i++) {
      u[i][0] = 0.0;
      p[i][0] = 0.0;
      q[i][0] = u[i][0];
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (j = 1; j <= 58; j++) {
        p[i][j] = -c * p[i][j - 1] - f * p[j - 1][i] + u[i][j];
        q[i][j] = -a * q[i][j - 1] - d * q[j - 1][i] + v[i][j];
        u[i][j] = p[i][j] - f * (q[i][j] - b * u[j][i]);
        v[i][j] = q[i][j] - a * (u[i][j] - f * v[j][i]);
      }
    }
  }
//#pragma endscop
}