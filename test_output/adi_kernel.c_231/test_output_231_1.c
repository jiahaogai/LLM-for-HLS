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
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      v[0][i] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = v[0][i];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 59; j++) {
        p[i][j] = -a * p[i][j - 1] - d * p[j - 1][i] + e * p[j - 1][j] ;
        q[i][j] = -b * v[j - 1][i] - f * u[i][j - 1] + d * q[j - 1][i] + e * q[j - 1][j] ;
        v[j][i] = -c * v[j - 1][i] - f * u[j - 1][i] + c * v[j - 1][j] + f * u[j - 1][j] ;
      }
      v[60][i] = 1.0;
      q[i][60] = v[60][i];
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      u[i][0] = 0.0;
      p[i][0] = 0.0;
      q[i][0] = v[0][i];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 59; j++) {
        p[i][j] = -a * p[i][j - 1] - d * p[j - 1][i] + e * p[j - 1][j] ;
        q[i][j] = -b * v[j - 1][i] - f * u[i][j - 1] + d * q[j - 1][i] + e * q[j - 1][j] ;
        u[i][j] = -c * u[i][j - 1] - f * p[j - 1][i] + c * u[i][j - 1] + f * p[j - 1][j] ;
      }
      u[i][60] = 0.0;
      q[i][60] = v[60][i];
    }
  }
//#pragma endscop
}