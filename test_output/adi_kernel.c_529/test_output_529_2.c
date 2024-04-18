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
  c = mul2 / 2.0;
  d = 1.0 + mul2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      v[0][i] = 1.0 / ((double )(i * i));
      a = -mul1 / ((double )((i + 1) * (i + 1)));
      b = 1.0 + mul1;
      c = mul2 / ((double )((j + 1) * (j + 1)));
      d = 1.0 + mul2;
      e = a * v[0][i] - c * u[i][0];
      f = b * v[0][i] - d * u[i][0];
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (j = 1; j < 59; j++) {
        tmp = a * v[j][i] - c * u[i][j];
        v[j][i] = b * v[j][i] - d * u[i][j];
        u[i][j] = e * u[i][j] + f * u[i][j - 1] + tmp * u[i][j + 1] ;
      }
      u[i][0] = v[i][0] - d * u[i][0];
      v[0][i] = e;
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      p[i][0] = -v[i][0] / u[0][i];
      a = -mul1 / ((double )((i + 1) * (i + 1)));
      b = 1.0 + mul1;
      c = mul2 / ((double )((j + 1) * (j + 1)));
      d = 1.0 + mul2;
      e = a * p[i][0] - c * q[i][0];
      f = b * p[i][0] - d * q[i][0];
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (j = 1; j < 59; j++) {
        tmp = a * p[i][j] - c * q[i][j];
        p[i][j] = b * p[i][j] - d * q[i][j];
        q[i][j] = e * q[i][j] + f * q[i][j - 1] + tmp * q[i][j + 1] ;
      }
      q[i][0] = p[i][0] - c * q[i][0];
      p[i][0] = e;
    }
  }
//#pragma endscop
}