#pragma ACCEL kernel

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
  for (t = 1; t <= 40; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      v[0][i] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = v[0][i];
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (j = 1; j < 59; j++) {
        p[i][j] = -a * p[i][j - 1] - d * p[j - 1][i] + u[i][j];
        q[i][j] = -b * q[i][j - 1] - e * q[j - 1][i] + v[i][j];
      }
      j = 59;
      v[i][j] = 1.0;
      q[i][j] = f / q[i][j - 1];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = j - 1; j >= 1; j--) {
        q[i][j] = q[i][j] - q[i][j + 1] * c / p[j + 1][i];
      }
      q[i][j] = q[i][j] * p[j][i];
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      u[i][0] = 1.0;
      p[i][0] = 0.0;
      u[i][0] = v[i][0];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 59; j++) {
        p[i][j] = -a * p[i][j - 1] - d * p[j - 1][i] + u[i][j];
        u[i][j] = b * u[i][j - 1] - e * u[j - 1][i] + v[i][j];
      }
      j = 59;
      u[i][j] = 1.0;
      u[i][j] = v[i][j] - d * u[j - 1][i];
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (j = j - 1; j >= 1; j--) {
        u[i][j] = u[i][j] - f * q[j][i] / p[j][i];
      }
      u[i][j] = u[i][j] * p[j][i];
    }
  }
//#pragma endscop
}