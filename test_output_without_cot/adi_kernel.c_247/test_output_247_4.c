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
  mul2 = B2 * 2.0 * DY * DY;
  a = -mul1 / (mul1 + mul2);
  b = 1.0 + a;
  c = mul2 / (mul1 + mul2);
  d = 1.0 - c;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      v[0][i] = 1.0;
      p[i][0] = 1.0;
      q[i][60] = 1.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (j = 1; j < 59; j++) {
        v[i][j] = -1.0 * DT / DX * (u[i][j + 1] - u[i][j - 1]) + v[i][j - 1];
        p[i][j] = -1.0 * DT / (DX * DX) * (u[i + 1][j] - 2.0 * u[i][j] + u[i - 1][j]) + DT / (2.0 * (1.0 + a) * DX) * (v[i + 1][j] - v[i - 1][j]) + p[i][j - 1];
      }
      q[i][0] = 1.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      for (j = 1; j < 59; j++) {
        q[i][j] = -1.0 * DT / DY * (u[j + 1][i] - u[j - 1][i]) + q[i][j - 1];
      }
    }
//Row Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
    for (i = 1; i < 59; i++) {
      u[i][0] = 1.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (j = 1; j < 59; j++) {
        u[i][j] = DT / (1.0 + a) * (b * v[i][j] - c * p[i][j] + d * q[i][j]) + u[i][j - 1];
      }
      u[i][60] = 1.0;
    }
  }
//#pragma endscop
}