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
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      v[0][i] = 0.0;
      p[i][0] = 0.0;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 59; j++) {
        v[i][j] = -a * (u[i][j] - u[i][j - 1]) - b * (u[i][j] - 2.0 * u[i][j] + u[i][j + 1]) + d * (u[i][j] - u[i - 1][j] - u[i + 1][j]);
        p[i][j] = -c * (v[i][j] - v[i][j - 1]) - d * (v[i][j] - v[i - 1][j] - v[i + 1][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (j = 1; j < 59; j++) {
        u[i][j] = u[i][j] + DT * (f[i][j] + k[i][j] - p[i][j] + q[i][j]);
        v[i][j] = v[i][j] + DT * (-p[i][j] + q[i][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    for (i = 1; i < 59; i++) {
      q[i][0] = 0.0;
      v[i][0] = 0.0;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      for (j = 1; j < 59; j++) {
        q[i][j] = -b * (v[i][j] - v[i][j - 1]) - d * (v[i][j] - v[i - 1][j] - v[i + 1][j]) + a * (u[i][j] - u[i][j - 1] - 2.0 * u[i][j] + u[i][j + 1] + v[i][j] - v[i - 1][j] - v[i + 1][j]);
        u[i][j] = u[i][j] + DT * (f[i][j] + k[i][j] - p[i][j] - q[i][j] - u[i][j] + v[i][j]);
      }
    }
  }
}