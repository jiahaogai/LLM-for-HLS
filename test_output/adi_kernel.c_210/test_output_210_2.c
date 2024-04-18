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
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      v[0][i] = 0.0;
      p[i][0] = 0.0;
      q[i][0] = v[0][i];
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (j = 1; j < 59; j++) {
        v[i][j] = ((a * (u[i][j + 1] - u[i][j - 1])) + (b * (u[i + 1][j] - u[i - 1][j]))) + u[i][j];
        p[i][j] = ((d * (v[i + 1][j] - v[i - 1][j])) + (e * (v[i][j + 1] - v[i][j - 1]))) + p[i][j];
        q[i][j] = ((a * (q[i][j + 1] - q[i][j - 1])) + (b * (q[i + 1][j] - q[i - 1][j]))) + v[i][j];
      }
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      u[i][0] = 0.0;
      p[i][0] = 0.0;
      q[i][0] = u[i][0];
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (j = 1; j < 59; j++) {
        u[i][j] = ((f * (v[i][j + 1] - v[i][j - 1])) + (c * (p[i + 1][j] - p[i - 1][j]))) + u[i][j];
        p[i][j] = ((d * (q[i + 1][j] - q[i - 1][j])) + (e * (p[i][j + 1] - p[i][j - 1]))) + p[i][j];
        q[i][j] = ((f * (u[i][j + 1] - u[i][j - 1])) + (c * (q[i + 1][j] - q[i - 1][j]))) + v[i][j];
      }
    }
  }
//#pragma endscop
}