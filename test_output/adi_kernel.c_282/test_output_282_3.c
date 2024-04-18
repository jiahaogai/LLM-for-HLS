#pragma ACCEL kernel

void kernel_adi(int tsteps,int n,double u[60][60],double v[60][60],double p[60][60],double q[60][60])
{
  int t;
  int i;
  int j;
  int k;
  int idx;
  int idy;
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
      a = mul1 * ((double )(i * 2 - 1));
      b = 1.0 + mul1;
      c = a;
      d = mul2 * ((double )(j * 2 - 1));
      e = 1.0 + mul2;
      f = d;
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 59; j++) {
        idx = t * 60 * 60 + i * 60 + j;
        v[j][i] = (a + v[j][i]) * u[j][i] + (f + v[j][i + 1]) * u[j][i + 1] - c / DX * (p[j][i] - p[j][i + 1]);
        u[j][i] = b * u[j][i] + d * u[j][i + 1] + e * (p[j + 1][i] - p[j][i]) / DY - f * v[j][i];
      }
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
    for (i = 1; i < 59; i++) {
      d = mul2 * ((double )(i * 2 - 1));
      e = 1.0 + mul2;
      f = d;
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (j = 1; j < 59; j++) {
        idy = t * 60 * 60 + i * 60 + j;
        q[j][i] = e * q[j][i] + f * q[j + 1][i] - d / DX * (u[j][i] - u[j][i + 1]) + v[j][i] * p[j][i];
        p[j][i] = b * p[j][i] + d * p[j][i + 1] + a / DY * (u[j + 1][i] - u[j][i]) - v[j][i + 1] * q[j][i];
      }
    }
  }
//#pragma endscop
}