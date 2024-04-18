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
  mul2 = B2 * DY * DY;
  a = -mul1 / (mul1 + mul2);
  b = -mul2 / (mul1 + mul2);
  c = 1.0 + 2.0 * mul1 / (mul1 - mul2);
  d = 1.0 + 2.0 * mul2 / (mul1 - mul2);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 39; t++) {
//Column Sweep
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      v[0][i] = 0.0;
      p[i][0] = 0.0;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (j = 1; j < 59; j++) {
        v[i][j] = a * (u[i][j + 1] - u[i][j - 1]) + b * (u[j + 1][j] - u[j - 1][j]) + c * u[i][j] - d * q[i][j];
        p[i][j] = -d * (p[i][j + 1] - p[i][j - 1]) - b * (p[j + 1][j] - p[j - 1][j]) + c * (p[i][j + 1] - p[i][j - 1]) + a * (p[j + 1][j] - p[j - 1][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      q[i][0] = 0.0;
      u[i][0] = 0.0;
    }
    
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (j = 1; j < 59; j++) {
        q[i][j] = -d * (v[i][j + 1] - v[i][j - 1]) - b * (v[j + 1][j] - v[j - 1][j]) + c * (v[i][j + 1] - v[i][j - 1]) + a * (q[i][j + 1] - q[i][j - 1]);
        u[i][j] = p[i][j] - d * (u[i + 1][j] - u[i - 1][j]) + c * (u[i + 1][j] - u[i - 1][j]) - a * (u[j + 1][i] - u[j - 1][i]) + b * (u[j + 1][i] - u[j - 1][i]);
      }
    }
  }
}