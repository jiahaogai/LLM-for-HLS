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
  b = 1.0 + a * DX * DX;
  c = a * DX * DY;
  d = -mul2 / 2.0;
  e = 1.0 + d * DY * DY;
  f = d * DX * DY;
  
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
        double sum = u[j][i] * p[i][j -1] + v[j][i] * q[i][j -1];
        p[i][j] = p[i][j -1] - u[j][i] * p[i][j -1] + v[j][i] * p[i][j -1] ;
        q[i][j] = q[i][j -1] - u[j][i] * q[i][j -1] + v[j][i] * q[i][j -1] + sum * DT / ((double )(1 + a * DX * DX + d * DY * DY));
      }
      v[60 -1][i] = 1.0;
      q[i][60 -1] = -v[60 -1][i] / d + 2.0 * q[i][60 -2] - q[i][60 -3];
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      u[i][0] = 1.0;
      p[i][0] = 0.0;
      q[i][0] = u[i][0] * p[i][0] + v[i][0] * q[i][0];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 59; j++) {
        double sum = u[i][j] * p[i][j -1] + v[i][j] * q[i][j -1];
        p[i][j] = p[i][j -1] - u[i][j] * p[i][j -1] + v[i][j] * p[i][j -1] ;
        q[i][j] = q[i][j -1] - u[i][j] * q[i][j -1] + v[i][j] * q[i][j -1] + sum * DT / ((double )(1 + a * DX * DX + d * DY * DY));
      }
      u[i][60 -1] = 1.0;
      p[i][60 -1] = -u[i][60 -1] / a + 2.0 * p[i][60 -2] - p[i][60 -3];
    }
  }
//#pragma endscop
}